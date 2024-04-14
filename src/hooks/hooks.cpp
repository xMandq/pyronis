#include <hooks/hooks.hpp>
#include <menu/menu.hpp>
#include <utils/console.hpp>
#include <minhook/include/MinHook.h>
#include <magic_enum/magic_enum.hpp>
#include <game/utils/text_scanner.hpp>

#include <stdexcept>
#include <format>
#include <sstream>
#include <regex>

void hook_function(auto& function, const auto& hook_function) {
	void* address = function;
	void* original = nullptr;

	if (MH_CreateHook(address, hook_function, &original) != MH_OK)
		throw std::runtime_error("failed to create hook");

	if (MH_EnableHook(address) != MH_OK)
		throw std::runtime_error("failed to enable hook");

	function = reinterpret_cast<decltype(function)>(original);
}

void hooks::install() {
	if (MH_Initialize() != MH_OK)
		throw std::runtime_error("failed to initialize minhook");

    //hook_function(gt::send_packet, send_packet_hook); // will check later
	hook_function(gt::send_packet_raw, send_packet_raw_hook);
	hook_function(gt::collide, collide_hook);
    hook_function(gt::server_info_http_finish, server_info_http_finish_hook);
	hook_function(gt::bumped_bouncy, bumped_bouncy_hook);
	hook_function(gt::can_see_ghosts, can_see_ghosts_hook);
	hook_function(gt::is_checkpoint, is_checkpoint_hook);
	hook_function(gt::on_punched, on_punched_hook);
	hook_function(gt::check_item_for_updates, check_item_for_updates_hook);
	hook_function(gt::handle_touch_at_world_coordinates, handle_touch_at_world_coordinates_hook);

	hook_function(gt::end_scene, end_scene_hook);
	original_wnd_proc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(gt::hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&wnd_proc_hook)));

	console::print_good("installed hooks");
}

void hooks::send_packet_hook(net_message_type type, std::string packet, void* peer) {


	gt::send_packet(type, packet, peer);
}

void hooks::send_packet_raw_hook(net_message_type type, const void* data, std::int32_t data_size, std::uint8_t* unk1, void* peer, std::uint32_t flags) {
	using enum game_packet_type;

	if (type != net_message_type::game_packet || data_size != sizeof(game_packet_t)) // this should never happen
		return;

	game_packet_t* packet = const_cast<game_packet_t*>(static_cast<const game_packet_t*>(data));

	switch (packet->type) {
	case state:
		//if (cheats::ghost_mode)
		//	return;

		//// if u are standing on spike for too long u get ban, this bypasses it
		if (cheats::anti_deadly)
			memory::remove_flag(packet->flags, visual_state::standing);

		if (cheats::fake_lag)
			memory::add_flag(packet->flags, visual_state::spawn);

		if (cheats::super_punch && memory::has_flag(packet->flags, visual_state::punch))
			memory::add_flag(packet->flags, visual_state::power_up_punch_end);

		if (cheats::walk_in_air)
			packet->vec2 = { 0.f, 0.f };

		break;

	case got_punched:
		if (cheats::anti_zombie)
			return;
		break;

	case app_integrity_fail:
		gt::log_to_console(std::format("`#pyronis:`` `oblocking client hack report`` `5(type {})``", packet->int3));
		return;
		break;

	default:
		break;
	}

	console::println<console::color::green>(std::format("sending game packet '{}'", magic_enum::enum_name(packet->type)));

	gt::send_packet_raw(type, data, data_size, unk1, peer, flags);
}

bool hooks::collide_hook(world_tile_map_t* _this, float unk1, float unk2, float unk3, float unk4, int unk5, bool unk6) {
	if (cheats::walk_in_air && !gt::get_game_logic()->local_player->down_key_state)
		return true;

	return gt::collide(_this, unk1, unk2, unk3, unk4, unk5, unk6);
}

void hooks::bumped_bouncy_hook(net_avatar_t* _this, tile_t* unk1, float* unk2, float* unk3) {
	if (cheats::anti_bouncy)
		return;

	gt::bumped_bouncy(_this, unk1, unk2, unk3);
}

void hooks::server_info_http_finish_hook(variant_list_t* var_list) {
    console::println(var_list->get(1).get_string());
    gt::server_info_http_finish(var_list);
}

bool hooks::can_see_ghosts_hook(std::int32_t item_id) {
	if (cheats::see_ghosts)
		return true;

	return gt::can_see_ghosts(item_id);
}

bool hooks::is_checkpoint_hook(tile_t* _this) {
	if (cheats::anti_checkpoint)
		return false;

	return gt::is_checkpoint(_this);
}

void hooks::on_punched_hook(net_avatar_t* _this, vec2f_t unk1, net_avatar_t* puncher) {
	if (cheats::anti_knockback)
		return;

	gt::on_punched(_this, unk1, puncher);
}

void hooks::check_item_for_updates_hook(item_info_t* _this, std::vector<int/*file_update_t*/>* file_updates) {
	if (cheats::skip_file_updates) {
		return;
	}

	gt::check_item_for_updates(_this, file_updates);
}

void hooks::handle_touch_at_world_coordinates_hook(level_touch_component_t* _this, vec2f_t* pos, bool unk1) {
	if (cheats::click_tp && (GetKeyState(VK_CONTROL) & 0x8000)) {
		net_avatar_t* local_player = gt::get_game_logic()->local_player;

		vec2i_t start = local_player->get_tile_pos();
		vec2i_t goal = { static_cast<std::int32_t>(pos->x / 32.f), static_cast<std::int32_t>(pos->y / 32.f) };
		if (start == goal)
			return;

		auto path = gt::find_path(start, goal);
		if (path.empty())
			return;

		std::size_t count = 0;
		for (vec2i_t pos : path) {
			if (++count % 7 == 0 || count == path.size()) {
				game_packet_t packet = {};
				packet.type = game_packet_type::state;
				packet.vec1 = { static_cast<float>(pos.x) * 32.f, static_cast<float>(pos.y) * 32.f };
				gt::send_game_packet(packet);
			}
		}

		local_player->set_pos_at_tile(goal);
		return;
	}

	gt::handle_touch_at_world_coordinates(_this, pos, unk1);
}

HRESULT hooks::end_scene_hook(IDirect3DDevice9* _this) {
	menu::render();
	return gt::end_scene(_this);
}

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

LRESULT hooks::wnd_proc_hook(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
        return TRUE;

    if (msg == WM_KEYUP && wparam == VK_INSERT) {
        menu::show = !menu::show;
        return TRUE;
    }

    const ImGuiIO& io = ImGui::GetIO();

    bool mouse =
        msg == WM_LBUTTONDOWN ||
        msg == WM_RBUTTONDOWN ||
        msg == WM_LBUTTONDBLCLK ||
        msg == WM_RBUTTONDBLCLK ||
        msg == WM_MOUSEWHEEL;

    if (io.WantTextInput || (io.WantCaptureMouse && mouse))
        return TRUE;

    return CallWindowProc(original_wnd_proc, hwnd, msg, wparam, lparam);
}
