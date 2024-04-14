#pragma once
#include <game/world/tile_extra.hpp>
#include <game/utils/math.hpp>

#include <cstdint>

enum class tile_flag : std::uint16_t {
	none = 0x0,
	extra_data = 0x1,
	locked = 0x2,
	spliced_tree = 0x4,
	tree_will_drop_seed = 0x8,
	tree = 0x10,
	flipped = 0x20,
	enabled = 0x40,
	public_ = 0x80,
	extra_frame = 0x100,
	silenced = 0x200,
	water = 0x400,
	glue = 0x800,
	fire = 0x1000,
	red = 0x2000,
	green = 0x4000,
	blue = 0x8000
};

#pragma pack(push, 1)
class tile_t {
public:
	vec2f_t get_world_pos() const noexcept {
		return { 
			static_cast<float>(pos.x) * 32.f,
			static_cast<float>(pos.y) * 32.f
		};
	}

	std::uint8_t pad1[4];
	std::uint16_t foreground; // 0x4
	std::uint8_t pad2[10];
	std::uint16_t background; // 0x10
	tile_flag flags; // 0x12
	vec2_t<std::uint8_t> pos; // 0x14
	std::uint8_t pad3[18];
	rectf_t collision_rect; // 0x28
	tile_extra_t* extra; // 0x38
	std::uint8_t pad4[24];
	std::uint8_t hit_count; // 0x58
	std::uint8_t pad5[87];
};
#pragma pack(pop)

static_assert(sizeof(tile_t) == 0xb0);
