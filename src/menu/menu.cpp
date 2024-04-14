#include <menu/menu.hpp>
#include <game/gt.hpp>
#include <utils/console.hpp>
#include <magic_enum/magic_enum.hpp>

#include <sstream>

void menu::setup() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;
	ImGui_ImplDX9_Init(gt::get_renderer()->device);
	ImGui_ImplWin32_Init(gt::hwnd);

	console::print_good("initialized imgui");
}

void menu::render() noexcept {
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (show) {
		ImGui::SetNextWindowPos({ 10.f, 10.f }, ImGuiCond_Once);
		ImGui::SetNextWindowSize({ 550.f, 350.f }, ImGuiCond_Once);
		ImGui::Begin("pyronis", &show, ImGuiWindowFlags_NoCollapse);

		ImGui::BeginTabBar("tabs");

		if (ImGui::BeginTabItem("cheats")) {
			cheats_page();
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("game")) {
			game_page();
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("debug")) {
			debug_page();
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
		ImGui::End();
	}

	render_overlays();
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void menu::render_overlays() noexcept {
	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
	if (draw_list == nullptr)
		return;

	game_logic_component_t* game_logic = gt::get_game_logic();
	item_info_manager_t* item_info_manager = gt::get_item_info_manager();
	if (game_logic == nullptr || item_info_manager == nullptr)
		return;

	world_t* world = game_logic->world;
	world_renderer_t* world_renderer = game_logic->world_renderer;
	if (world == nullptr || world_renderer == nullptr)
		return;

	world_tile_map_t& tile_map = world->tile_map;
	const world_camera_t& camera = world_renderer->camera;

	if (cheats::tile_info && (GetKeyState(VK_CONTROL) & 0x8000)) {
		ImVec2 mouse_pos = ImGui::GetMousePos();
		tile_t* tile = tile_map.get_tile_at_world_pos(camera.screen_to_world({ mouse_pos.x, mouse_pos.y }));

		if (tile == nullptr)
			return;

		vec2f_t tile_screen_pos = camera.world_to_screen(tile->get_world_pos());
		draw_list->AddRectFilled(
			{
				tile_screen_pos.x,
				tile_screen_pos.y
			},
			{
				tile_screen_pos.x + 32.f * camera.zoom_level.x,
				tile_screen_pos.y + 32.f * camera.zoom_level.y
			},
			ImColor(1.f, 0.f, 0.f, 0.5f)
		);

		ImGui::BeginTooltip();

		ImGui::Text("foreground item: %s", item_info_manager->get_item_name(tile->foreground).c_str());
		ImGui::Text("background item: %s", item_info_manager->get_item_name(tile->background).c_str());
		ImGui::Text("position: %d,%d", tile->pos.x, tile->pos.y);
		ImGui::Text("hit count: %d", tile->hit_count);

		if (tile->flags != tile_flag::none)
			ImGui::Text("flags: %s", magic_enum::enum_flags_name(tile->flags).data());

		if (tile->extra != nullptr) {
			ImGui::SeparatorText("extra data");
			ImGui::Text("type: %s", magic_enum::enum_name(tile->extra->type).data());

			using enum tile_extra_type;
			switch (tile->extra->type) {
			case door:
			case sign:
				ImGui::Text("label: %s", tile->extra->label.c_str());
				break;

			case lock:
				ImGui::Text("owner: %d", tile->extra->owner);
				for (std::uint32_t admin : tile->extra->access_list)
					ImGui::Text("admin: %d", admin);
				break;

			case tree:
				ImGui::Text("growth: %d", tile->extra->growth);
				ImGui::Text("fruit count: %d", tile->extra->fruit_count);
				break;

			case vending_machine:
				ImGui::Text("item: %s", item_info_manager->get_item_name(tile->extra->item_id).c_str());
				ImGui::Text("price: %d", tile->extra->item_price);
				break;

			default:
				ImGui::TextColored({ 1.f, 0.f, 0.f, 1.f }, "unknown data");
				break;
			}
		}

		ImGui::EndTooltip();
	}
}
