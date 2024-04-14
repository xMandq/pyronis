#pragma once
#include <game/entity/component.hpp>
#include <game/world/world.hpp>
#include <game/world/world_renderer.hpp>
#include <game/player/net_avatar.hpp>
#include <game/player/player_items.hpp>
#include <game/manager/net_object_manager.hpp>
#include <game/manager/text_manager.hpp>
#include <game/manager/hud_indicator_manager.hpp>
#include <game/manager/effect_manager.hpp>

#pragma pack(push, 1)
class game_logic_component_t : public entity_component_t { // real size is 1184
public:
	std::uint8_t pad1[80];
	world_t* world; // 0x108
	world_renderer_t* world_renderer; // 0x110
	std::uint8_t pad2[72];
	net_object_manager_t net_object_manager; // 0x160
	net_avatar_t* local_player; // 0x1b0
	text_manager_t text_manager; // 0x1b8
	hud_indicator_manager_t hud_indicator_manager; // 0x1e8
	player_items_t player_items; // 0x208
	effect_manager_t effect_manager; // 0x288
};
#pragma pack(pop)

