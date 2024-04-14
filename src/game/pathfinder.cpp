#include <game/gt.hpp>

#include <vector>
#include <cmath>
#include <array>
#include <algorithm>

struct node_t {
	node_t(vec2i_t pos) noexcept : pos(pos), g_cost(0), h_cost(0), parent(nullptr) {}

	vec2i_t pos;
	std::uint32_t g_cost, h_cost;
	node_t* parent;
};

node_t* find_node(const std::vector<node_t*>& set, vec2i_t pos) noexcept {
	auto it = std::find_if(set.begin(), set.end(), [pos](node_t* node) { return node->pos == pos; });

	if (it != set.end())
		return *it;

	return nullptr;
}

std::uint32_t calculate_heuristic(vec2i_t pos, vec2i_t goal) noexcept {
	return std::abs(pos.x - goal.x) + std::abs(pos.y - goal.y);
}

std::vector<vec2i_t> gt::find_path(const vec2i_t& start, const vec2i_t& goal) noexcept {
	if (start == goal)
		return {};

	world_t* world = gt::get_game_logic()->world;
	net_avatar_t* local_player = gt::get_game_logic()->local_player;

	if (world == nullptr || local_player == nullptr)
		return {};

	tile_t* start_tile = world->tile_map.get_tile(start);
	tile_t* goal_tile = world->tile_map.get_tile(goal);

	if (start_tile == nullptr || is_collidable(start_tile, local_player->user_id, world, true) ||
		goal_tile == nullptr || is_collidable(goal_tile, local_player->user_id, world, true))
		return {};

	constexpr std::array<vec2i_t, 4> directions = {
		vec2i_t{ -1, 0 },
		vec2i_t{ 0, -1 },
		vec2i_t{ 1, 0 },
		vec2i_t{ 0, 1 }
	};

	std::vector<node_t*> open_set, closed_set;
	open_set.push_back(new node_t{ goal });

	node_t* current_node = nullptr;
	while (!open_set.empty()) {
		auto it = std::min_element(open_set.begin(), open_set.end(),
			[](node_t* a, node_t* b) {
				return (a->g_cost + a->h_cost) < (b->g_cost + b->h_cost);
			});

		current_node = *it;
		if (current_node->pos == start)
			break;

		closed_set.push_back(current_node);
		open_set.erase(it);

		tile_t* current_tile = world->tile_map.get_tile(current_node->pos);
		item_info_t* current_info = gt::get_item_info_manager()->get_item(current_tile->foreground);

		for (vec2i_t dir : directions) {
			vec2i_t neighbor_pos = current_node->pos + dir;

			if (find_node(closed_set, neighbor_pos) != nullptr)
				continue;

			tile_t* neighbor_tile = world->tile_map.get_tile(neighbor_pos);
			if (neighbor_tile == nullptr || is_collidable(neighbor_tile, local_player->user_id, world, true))
				continue;

			item_info_t* neighbor_info = gt::get_item_info_manager()->get_item(neighbor_tile->foreground);
			if (neighbor_info == nullptr)
				continue;

			if (neighbor_info->collision == tile_collision_type::one_way &&
				!memory::has_flag(neighbor_tile->flags, tile_flag::flipped) && current_node->pos.x < neighbor_pos.x)
				continue;

			if (neighbor_info->collision == tile_collision_type::one_way &&
				memory::has_flag(neighbor_tile->flags, tile_flag::flipped) && current_node->pos.x > neighbor_pos.x)
				continue;

			if (current_info->collision == tile_collision_type::jump_through && current_node->pos.y > neighbor_pos.y)
				continue;

			if (current_info->collision == tile_collision_type::jump_down && current_node->pos.y < neighbor_pos.y)
				continue;

			if (current_info->collision == tile_collision_type::one_way &&
				!memory::has_flag(current_tile->flags, tile_flag::flipped) && current_node->pos.x < neighbor_pos.x)
				continue;

			if (current_info->collision == tile_collision_type::one_way &&
				memory::has_flag(current_tile->flags, tile_flag::flipped) && current_node->pos.x > neighbor_pos.x)
				continue;

			std::uint32_t cost = current_node->g_cost + 1;

			node_t* neighbor_node = find_node(open_set, neighbor_pos);
			if (neighbor_node == nullptr) {
				neighbor_node = new node_t(neighbor_pos);
				neighbor_node->parent = current_node;
				neighbor_node->g_cost = cost;
				neighbor_node->h_cost = calculate_heuristic(neighbor_pos, start);
				open_set.push_back(neighbor_node);
			}
			else if (cost < neighbor_node->g_cost) {
				neighbor_node->parent = current_node;
				neighbor_node->g_cost = cost;
			}
		}
	}

	if (current_node == nullptr || current_node->pos != start) {
		for (node_t* node : open_set)
			delete node;

		for (node_t* node : closed_set)
			delete node;

		return {};
	}

	std::vector<vec2i_t> path;

	while (current_node != nullptr) {
		path.push_back(current_node->pos);
		current_node = current_node->parent;
	}

	for (node_t* node : open_set)
		delete node;

	for (node_t* node : closed_set)
		delete node;

	return path;
}