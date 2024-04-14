#include <menu/menu.hpp>
#include <game/gt.hpp>
#include <magic_enum/magic_enum.hpp>

#include <format>

entity_t* selected_entity = nullptr;
bool selected_found = false;

void imgui_entity(entity_t* entity) {
	bool this_selected = selected_entity == entity;

	if (entity->children.empty()) {
		ImGui::Bullet();
		ImGui::Selectable(entity->name.c_str(), this_selected);

		if (ImGui::IsItemClicked())
			selected_entity = entity;
	}
	else {
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
		if (this_selected)
			flags |= ImGuiTreeNodeFlags_Selected;

		bool open = ImGui::TreeNodeEx(entity->name.c_str(), flags);

		if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			selected_entity = entity;

		if (open) {
			for (entity_t* child : entity->children)
				imgui_entity(child);

			ImGui::TreePop();
		}
	}

	if (selected_entity == entity)
		selected_found = true;
}

void imgui_variant_db(const variant_db_t& var_db) {
	if (!var_db.data.empty()) {
		if (ImGui::TreeNode("variants")) {
			for (const auto& [name, variant] : var_db.data) {
				if (ImGui::TreeNode(std::format("{} ({})", name, magic_enum::enum_name(variant->get_type())).c_str())) {

					switch (variant->get_type()) {
					case variant_type::float32:
						ImGui::InputFloat("value", &variant->float_value);
						break;

					case variant_type::string: {
						char* text = const_cast<char*>(variant->string_value.c_str());
						ImGui::InputText("value", text, 1024);
						variant->string_value = text;
						break;
					}

					case variant_type::vec2:
						ImGui::InputFloat("x value", &variant->vec2_value.x);
						ImGui::InputFloat("y value", &variant->vec2_value.y);
						break;

					case variant_type::vec3:
						ImGui::InputFloat("x value", &variant->vec3_value.x);
						ImGui::InputFloat("y value", &variant->vec3_value.y);
						ImGui::InputFloat("z value", &variant->vec3_value.z);
						break;

					case variant_type::rect:
						ImGui::InputFloat("x value", &variant->rect_value.x);
						ImGui::InputFloat("y value", &variant->rect_value.y);
						ImGui::InputFloat("z value", &variant->rect_value.z);
						ImGui::InputFloat("w value", &variant->rect_value.w);
						break;

					case variant_type::uint32:
					case variant_type::int32:
						ImGui::InputInt("value", &variant->int_value);
						break;

					default:
						ImGui::TextColored({ 1.f, 0.f, 0.f, 1.f }, "unknown variant type");
						break;
					}

					ImGui::TreePop();
				}
			}
			ImGui::TreePop();
		}
	}

	if (!var_db.function_data.empty()) {
		if (ImGui::TreeNode("functions")) {
			for (const auto& [name, function] : var_db.function_data)
				ImGui::BulletText("%s (0x%llx)", name.c_str(), function);
			ImGui::TreePop();
		}
	}
}

void menu::game_page() noexcept {
	ImGui::BeginTabBar("game tabs");

	if (ImGui::BeginTabItem("variant db")) {
		ImGui::BeginChild("variant db");
		imgui_variant_db(gt::get_app()->var_db);
		ImGui::EndChild();
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("items")) { // todo: item search with icons and better filters
		static char search[256];
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		ImGui::InputTextWithHint("##search", "search", search, IM_ARRAYSIZE(search));
		ImGui::BeginChild("items");
	
		for (const item_info_t& item : gt::get_item_info_manager()->items) {
			if (std::strlen(search) == 0 || item.name.find(search) != std::string::npos) {
				ImGui::Text("%d: %s, %d", item.id, item.name.c_str(), item.collision);
			}
		}
	
		ImGui::EndChild();
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("entity tree")) {
		ImGui::BeginChild("entity tree");
		ImGui::Columns(2, "entity columns", false);

		selected_found = false;
		imgui_entity(gt::get_entity_root());
		
		if (!selected_found) // lazy fix
			selected_entity = nullptr;
		
		ImGui::NextColumn();
		
		if (selected_entity != nullptr) {
			ImGui::SeparatorText(selected_entity->name.c_str());
		
			if (selected_entity->parent != nullptr)
				ImGui::Text("parent: %s", selected_entity->parent->name.c_str());
		
			imgui_variant_db(selected_entity->shared_db);
		
			if (!selected_entity->components.empty()) {
				if (ImGui::TreeNode("components")) {
					for (entity_component_t* component : selected_entity->components) {
						std::string text = std::format("{} (0x{:x})", component->name->c_str(), reinterpret_cast<std::uintptr_t>(component));
						if (component->shared_db.data.empty() && component->shared_db.function_data.empty()) {
							ImGui::BulletText(text.c_str());
						}
						else {
							if (ImGui::TreeNode(text.c_str())) {
								imgui_variant_db(component->shared_db);
								ImGui::TreePop();
							}
						}
					}
					ImGui::TreePop();
				}
		
			}
		}
		ImGui::EndColumns();
		ImGui::EndChild();
		ImGui::EndTabItem();
	}


	if (ImGui::BeginTabItem("textures")) {
		ImGui::BeginChild("textures");
		for (const auto& [name, resource] : gt::get_app()->resource_manager.data) {
			if (ImGui::TreeNode(name.c_str())) {
				const texture_d3d9_t& texture = gt::get_renderer()->textures[resource->surface->texture_id];
				ImGui::Image(texture.ptr, { static_cast<float>(texture.width), static_cast<float>(texture.height) }, { 0.f, 1.f }, { 1.f, 0.f });
				ImGui::TreePop();
			}
		}
	
		ImGui::EndChild();
		ImGui::EndTabItem();
	}

	ImGui::EndTabBar();
}
