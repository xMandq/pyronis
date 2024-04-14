#pragma once
#include <game/utils/math.hpp>
#include <cstdint>

enum class net_message_type : std::uint32_t {
	unknown,
	server_hello,
	generic_text,
	game_message,
	game_packet,
	error,
	track,
	client_log_request,
	client_log_response
};

enum class game_packet_type : std::uint8_t {
	state,
	call_function,
	update_status,
	tile_change_request,
	send_map_data,
	send_tile_update_data,
	send_tile_update_data_multiple,
	tile_activate_request,
	tile_apply_damage,
	send_inventory_state,
	item_activate_request,
	item_activate_object_request,
	send_tile_tree_state,
	modify_item_inventory,
	item_change_object,
	send_lock,
	send_item_database_data,
	send_particle_effect,
	set_icon_state,
	item_effect,
	set_character_state,
	ping_reply,
	ping_request,
	got_punched,
	app_check_response,
	app_integrity_fail,
	disconnect,
	battle_join,
	battle_event,
	use_door,
	send_parental,
	gone_fishin,
	steam,
	pet_battle,
	npc,
	special,
	send_particle_effect_v2,
	active_arrow_to_item,
	select_tile_index,
	send_player_tribute_data, 
	ftue_set_item_to_quick_inventory,
	pve_npc,
	pvpcard_battle,
	pve_apply_player_damage,
	pve_npc_position_update,
	set_extra_mods,
	on_step_on_tile_mod
};

struct game_packet_t {
	inline std::uint8_t* get_extra_data() noexcept {
		return reinterpret_cast<std::uint8_t*>(this) + sizeof(game_packet_t);
	}

	game_packet_type type;
	std::uint8_t byte1;
	std::uint8_t byte2;
	std::uint8_t byte3;
	std::int32_t int1;
	std::int32_t int2;
	std::uint32_t flags;
	float float1;
	std::int32_t int3;
	vec2f_t vec1;
	vec2f_t vec2;
	float float2;
	std::int32_t int4;
	std::int32_t int5;
	std::uint32_t extra_data_size;
};

static_assert(sizeof(game_packet_t) == 56);
