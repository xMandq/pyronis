#include <game/gt.hpp>
#include <utils/console.hpp>
#include <utils/memory.hpp>
#include <utils/random.hpp>

#include <stdexcept>
#include <string>
#include <format>
#include <fstream>
#include <thread>

void patch_integrity_check() {
	std::uintptr_t integrity_check_2 = memory::find_pattern("3B C1 75 08 85 C9", 2);

	if (integrity_check_2 == 0)
		throw std::runtime_error("integrity check 2 pattern not found");

	if (!memory::patch_bytes(integrity_check_2, "90 90"))
		throw std::runtime_error("failed to patch integrity check 2");
}

enum class find_mode {
	normal,
	call,
	load,
	function_start
};

void find_address(auto& dest, std::string_view pattern, find_mode mode, std::intptr_t offset = 0) {
	std::uintptr_t address = memory::find_pattern(pattern, offset);

	switch (mode) {
	case find_mode::call:
		address = memory::get_address_from_call(address);
		break;

	case find_mode::load:
		address = memory::get_address_from_load(address);
		break;

	case find_mode::function_start:
		address = memory::find_function_start(address);
		break;

	default:
		break;
	}

	if (address == 0)
		throw std::runtime_error(std::format("pattern '{}' not found", pattern));

	dest = reinterpret_cast<decltype(dest)>(address);
}

void find_addresses() {
	// globals
	find_address(gt::get_app, "5f c3 e8 ? ? ? ? 48 8b c8 33 d2", find_mode::call, 2);
	find_address(gt::get_entity_root, "48 e8 ? ? ? ? ? e8 ? ? ? ? 48 ? ? ? 48 8b ?", find_mode::call, 7);
	find_address(gt::get_client, "74 32 e8 ? ? ? ff 48 8b c8 e8 ? ? ? ff 48 85 c0", find_mode::call, 2);
	find_address(gt::get_game_logic, "e8 ? ? ? ? 44 8b a0 ? ? ? ?", find_mode::call);
	find_address(gt::get_item_info_manager, "e8 ? ? ? ? 48 8b c8 8b 57 ? e8 ? ? ? ? 48 85", find_mode::call);
	find_address(gt::log_to_console, "e8 ? ? ? ? 48 8b c8 e8 ? ? ? ? 90 48 8d 4d ? e8 ? ? ? ? e8", find_mode::call, 8);
	find_address(gt::send_packet, "02 00 00 00 e8 ? ? ? ? 90 48 8d ? ? ? e8 ? ? ? ? 90 48 8d 4c ? ? e8 ? ? ? ? 90 48 8d 4c ? ? e8 ? ? ? ? ? ? e8", find_mode::call, 4);
	find_address(gt::send_packet_raw, "7e ? 8b 95 a0", find_mode::function_start);
	find_address(gt::can_see_ghosts, "e8 ? ? ? ? 41 be ? ? ? ? 41 8b dc", find_mode::call);
	find_address(gt::server_info_http_finish, "48 8d ? ? 48 ? ? ? ? ? ? ? ? ? ? 4c 8d ? ? ? ? 8d ? ? 48 8d ? ? ? e8 ? ? ? ?", find_mode::function_start);

	// net avatar
	find_address(gt::on_punched, "b8 ? ? ? ? 66 39 03 75 ? 48 8b", find_mode::function_start);
	find_address(gt::bumped_bouncy, "e8 ? ? ? ? ? ? ? ? ? ? ? ? 8b ? e8 ? ? ? ? bd", find_mode::call);

	// tile
	find_address(gt::is_checkpoint, "e8 ? ? ? ? 84 c0 74 ? 0f b7 46 ? ? ? ? 8c", find_mode::call);
	find_address(gt::is_collidable, "48 8b ? e8 ? ? ? ? 84 ? 0f ? ? ? ? ? 0f ? ? ? ? 48 8b ? ? ? ? ? ? e8 ? ? ? ? 0f", find_mode::call, 3);

	// others
	find_address(gt::handle_touch_at_world_coordinates, "66 39 48 ? 0f 84 ? ? ? ? c6 05", find_mode::function_start);
	find_address(gt::collide, "e8 ? ? ? ? 48 ? c0 74 ? 48 ? ? 48 8b ? e8 ? ? ? ? b0", find_mode::call);
	find_address(gt::check_item_for_updates, "48 8d 15 ? ? ? ? e8 ? ? ? ? ff c3 e8", find_mode::call, 7);
	find_address(gt::create_text_label_entity, "48 8b cf e8 ? ? ? ? 48 8b d8 f3 0f 10 54 24", find_mode::call, 3);
	find_address(gt::get_surface_anim, "e8 ? ? ? ? 48 8b ? 48 ? ? 75 ? 48 8d ? ? e8 ? ? ? ? 48 8b", find_mode::call);

	// just addresses
	find_address(gt::anti_slide_address, "74 ? 48 8b ? ? ? e8 ? ? ? ? 81 ? ? ? ? ? 74", find_mode::normal);
	find_address(gt::anti_portal_address, "74 ? 41 ? ? ? ? ? ? 41 b0 ? 48 8b", find_mode::normal);
	find_address(gt::see_locked_doors_address, "40 ? ? 74 ? 48 8d ? ? ? ? ? 48 8d ? ? ? ? ? e8", find_mode::normal, 3);
	find_address(gt::touch_bypass_address, "3d ? ? ? ? 72 ? c6 ? ? ? ? ? ? c7", find_mode::normal, 5);
	find_address(gt::enable_pasting_address, "74 ? ? ? ? 75 ? 48 8b ? e8 ? ? ? ? 83 ? ? 75", find_mode::normal);
	find_address(gt::renderer, "48 8b 05 ? ? ? ? 41 83 ? ?", find_mode::load, 3);

	gt::end_scene = reinterpret_cast<decltype(gt::end_scene)>((*reinterpret_cast<void***>(gt::get_renderer()->device_ex))[42]);
}

void create_watermark() noexcept {
	using namespace random;

	entity_t* watermark = gt::create_text_label_entity(gt::get_entity_root(), "Watermark", 8.f, static_cast<float>(gt::window_size.y - 85), "pyronis");

	watermark->get_var("color")->set(
		(random_num(255) << 24) | // blue
		(random_num(255) << 16) | // green
		(random_num(255) << 8) |  // red
		255u                      // alpha
	);

	watermark->get_var("scale2d")->set(vec2f_t{ 0.5f, 0.5f });
	watermark->get_component_by_name("TextRender")->get_var("font")->set(1u);
	watermark->get_component_by_name("TextRender")->get_var("shadowColor")->set(150u);
}

void gt::setup() {
	using namespace console;

	MODULEINFO module_info = {};
	if (!GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &module_info, sizeof(MODULEINFO)))
		throw std::runtime_error("failed to get module information");

	base_address = reinterpret_cast<std::uintptr_t>(module_info.lpBaseOfDll);
	end_address = base_address + module_info.SizeOfImage;
	if (base_address == 0 || end_address == 0)
		throw std::runtime_error("invalid module address");

	hwnd = FindWindow(nullptr, "Growtopia");
	if (hwnd == nullptr)
		throw std::runtime_error("growtopia window not found");

	RECT rect = {};
	if (!GetWindowRect(gt::hwnd, &rect))
		throw std::runtime_error("failed to get window size");

	window_size.x = rect.left - rect.right;
	window_size.y = rect.bottom - rect.top;

	patch_integrity_check();
	print_good("patched integrity check");

	find_addresses();
	print_good("found addresses");

	//set_fps_limit(get_app(), 0.f);
	//print_good("unlocked fps limit");

	create_watermark();
	print_good("created watermark");

	gt::get_app()->get_var("move_down_primary")->set(83u);
	gt::get_app()->get_var("move_down_secondary")->set(40u);
}

renderer_context_d3d9_t* gt::get_renderer() noexcept {
	return *renderer;
}

void gt::send_generic_text(const std::string& packet) noexcept {
	enet_client_t* client = gt::get_client();
	if (client == nullptr || client->peer == nullptr)
		return;
	
	send_packet(net_message_type::generic_text, packet, client->peer);
}

void gt::send_game_message(const std::string& packet) noexcept {
	enet_client_t* client = gt::get_client();
	if (client == nullptr || client->peer == nullptr)
		return;

	send_packet(net_message_type::game_message, packet, client->peer);
}

void gt::send_game_packet(const game_packet_t& packet) noexcept {
	enet_client_t* client = gt::get_client();
	if (client == nullptr || client->peer == nullptr)
		return;

	send_packet_raw(net_message_type::game_packet, &packet, sizeof(game_packet_t), nullptr, client->peer, 0x1);
}