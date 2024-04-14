#pragma once
#include <game/world/tile.hpp>
#include <game/utils/math.hpp>

#include <vector>
#include <cstdint>

class world_t;

#pragma pack(push, 1)
class world_tile_map_t {
public:
	tile_t* get_tile(std::int32_t x, std::int32_t y) noexcept {
		if (x >= 0 && y >= 0 && size.x > x && size.y > y)
			return &tiles[static_cast<std::size_t>(y * size.x + x)];

		return nullptr;
	}

	tile_t* get_tile(const vec2i_t& pos) noexcept {
		return get_tile(pos.x, pos.y);
	}

	tile_t* get_tile_at_world_pos(const vec2f_t& pos) noexcept {
		return get_tile(
			static_cast<std::int32_t>(pos.x / 32.f), 
			static_cast<std::int32_t>(pos.y / 32.f)
		);
	}

	void* vftable;
	vec2i_t size;
	std::uint8_t pad1[8];
	std::vector<tile_t> tiles;
	world_t* parent_world;
};
#pragma pack(pop)
