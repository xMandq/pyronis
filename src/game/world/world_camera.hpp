#pragma once
#include <game/utils/math.hpp>

#include <cstdint>

class world_renderer_t;

#pragma pack(push, 1)
class world_camera_t {
public:
	vec2f_t world_to_screen(vec2f_t pos) const noexcept {
		pos -= camera_pos;
		pos *= zoom_level;
		return pos;
	}

	vec2f_t screen_to_world(vec2f_t pos) const noexcept {
		pos /= zoom_level;
		pos += camera_pos;
		return pos;
	}

	void* vftable;
	world_renderer_t* parent_world_renderer; // 0x8
	vec2f_t camera_pos; // 0x10
	vec2f_t local_player_pos; // 0x18 target render pos?
	std::uint8_t pad1[8];
	vec2f_t zoom_level; // 0x28
	std::uint8_t pad2[8];
	vec2f_t screen_size; // 0x38
	vec2f_t zoomed_screen_size; // 0x40
	std::uint8_t pad3[1];
	bool unk1; // 0x49
};

#pragma pack(pop)
