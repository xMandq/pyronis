#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_dx9.h>
#include <imgui/imgui_impl_win32.h>

#include <cstdint>
#include <string_view>

namespace menu {
	void setup();
	void render() noexcept;
	void render_overlays() noexcept;

	void cheats_page() noexcept;
	void game_page() noexcept;
	void debug_page() noexcept;

	inline bool show = true;
}

namespace cheats {
	inline bool anti_deadly = false;
	inline bool anti_bouncy = false;
	inline bool anti_damage = false;
	inline bool anti_checkpoint = false;
	inline bool anti_portal = false;
	inline bool anti_slide = false;
	inline bool anti_water = false;
	inline bool anti_zombie = false;
	inline bool anti_ghost = false;
	inline bool anti_knockback = false;
	inline bool anti_freeze = false;

	inline bool night_vision = false;
	inline bool see_fruits = false;
	inline bool see_ghosts = false;
	inline bool see_locked_doors = false;
	inline bool fake_lag = false;
	inline bool ghost_mode = false;
	inline bool mod_zoom = false;
	inline bool fast_punch = false;
	inline bool show_platform = false;

	inline bool click_tp = false;
	inline bool tile_info = false;
	inline bool walk_in_air = false;
	inline bool unlimited_jumps = false;
	inline bool super_punch = false;
	inline bool block_ads = false;
	inline bool touch_bypass = false;
	inline bool enable_pasting = false;
	inline bool auto_reconnect = false;
	inline bool skip_file_updates = false;
}