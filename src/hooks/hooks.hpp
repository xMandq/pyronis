#pragma once
#include <game/gt.hpp>

#include <string>
#include <cstdint>
#include <d3d9.h>

namespace hooks {
	void install();

	void send_packet_hook(net_message_type type, std::string packet, void* peer);
	void send_packet_raw_hook(net_message_type type, const void* data, std::int32_t data_size, std::uint8_t* unk1, void* peer, std::uint32_t flags);

	bool collide_hook(world_tile_map_t* _this, float unk1, float unk2, float unk3, float unk4, int unk5, bool unk6);
	void bumped_bouncy_hook(net_avatar_t* _this, tile_t* unk1, float* unk2, float* unk3);

	void server_info_http_finish_hook(variant_list_t* var_list);
	bool can_see_ghosts_hook(std::int32_t item_id);
	bool is_checkpoint_hook(tile_t* _this);
	void on_punched_hook(net_avatar_t* _this, vec2f_t unk1, net_avatar_t* puncher);
	void check_item_for_updates_hook(item_info_t* _this, std::vector<int/*file_update_t*/>* file_updates);
	void handle_touch_at_world_coordinates_hook(level_touch_component_t* _this, vec2f_t* pos, bool unk1);

	HRESULT end_scene_hook(IDirect3DDevice9* _this);
	LRESULT wnd_proc_hook(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	inline WNDPROC original_wnd_proc = nullptr;
}
