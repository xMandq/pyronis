#pragma once
#include <game/utils/math.hpp>
#include <game/utils/lock_float.hpp>

#include <cstdint>
#include <memory>

enum class visual_state : std::uint32_t {
	none = 0x0,
	unk_0x1 = 0x1,
	unk_0x2 = 0x2,
	spawn = 0x4,
	unk_0x8 = 0x8,
	flipped = 0x10,
	standing = 0x20,
	fire_damage = 0x40,
	jump = 0x80,
	got_killed = 0x100,
	punch = 0x200,
	place = 0x400,
	tile_change = 0x800,
	got_punched = 0x1000,
	respawn = 0x2000,
	object_collect = 0x4000,
	trampoline = 0x8000,
	damage = 0x10000,
	slide = 0x20000,
	parasol = 0x40000,
	unk_0x80000 = 0x80000, // used in gravity() and OnJump(), some bcape jump stuff
	swim = 0x100000,
	wall_hang = 0x200000,
	power_up_punch_start = 0x400000,
	power_up_punch_end = 0x800000,
	unk_0x1000000 = 0x1000000, // some tile change stuff
	unk_0x2000000 = 0x2000000, // used in AnimatedCapeLogics::CheckHayCartConditions
	unk_0x4000000 = 0x4000000, // more OnJump bcape things
	unk_0x8000000 = 0x8000000,
	acid_damage = 0x10000000,
};

enum class player_flag : std::uint32_t {
	none = 0x0,
	no_clip = 0x1,
	double_jump = 0x2,
	invisible = 0x4,
	no_hands = 0x8,
	no_face = 0x10,
	no_body = 0x20,
	devil_horns = 0x40,
	golden_halo = 0x80,
	unk_0x100,
	unk_0x200, // got when consumed spike juice
	spikeproof = 0x400,
	frozen = 0x800,
	cursed = 0x1000,
	duct_taped = 0x2000,
	bad_smell = 0x4000,
	shiny = 0x8000,
	zombie = 0x10000,
	unk_0x20000 = 0x20000,
	shadows = 0x40000,
	irradiated = 0x80000,
	spotlight = 0x100000,
	pineapple_skin_and_flag = 0x200000,
	pineapple_flag = 0x400000,
	unk_0x800000 = 0x800000,
	super_supporter = 0x1000000,
	pineapple_aura = 0x2000000,
	bubble = 0x4000000,
	wet = 0x8000000,
	mask1 = 0x10000000,
	mask2 = 0x20000000,
	mask3 = 0x40000000,
	mask4 = 0x80000000
};

enum class player_flags2 : std::uint32_t {

};

#pragma pack(push, 1)
class net_avatar_t /*: public net_moving_t*/ {
public:
	vec2i_t get_tile_pos() const noexcept {
		return { 
			static_cast<std::int32_t>((pos.x + size.x / 2.f) / 32.f), 
			static_cast<std::int32_t>((pos.y + size.y / 2.f) / 32.f) 
		};
	}

	void set_pos_at_tile(vec2i_t tile_pos) noexcept {
		pos.x = static_cast<float>(tile_pos.x) * 32.f + 6.f;
		pos.y = static_cast<float>(tile_pos.y) * 32.f + 2.f;
	}

	void* vftable;
	vec2f_t pos;
	vec2f_t size;
	vec2f_t encrypted_pos;
	vec2f_t encrypted_size;
	std::string name;
	std::int32_t net_id;
	std::uint8_t pad1[21];
	bool facing_left;
	std::uint8_t pad2[122];
	bool can_jump;
	std::uint8_t pad3[7];
	vec2_t<lock_float_t> velocity;
	std::uint8_t pad4[52];
	std::uint32_t freeze_state;
	std::int32_t user_id;
	std::uint8_t pad5[16];
	std::string country;
	std::uint8_t pad6[8];
	bool is_invis;
	bool is_mod;
	bool is_smod;
	std::uint8_t pad7[9];
	std::uint32_t bubble_state;
	player_flag flags;
	std::uint8_t pad8[20];
	bool down_key_state;
	std::uint8_t pad9[4];
	std::uint32_t punch_effect;
	std::uint8_t pad10[28];
	lock_float_t gravity;
	lock_float_t acceleration;
	lock_float_t speed;
	float water_speed;
};
#pragma pack(pop)
