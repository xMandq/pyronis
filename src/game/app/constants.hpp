#pragma once
#include <game/utils/lock_float.hpp>
#include <game/utils/math.hpp>

#pragma pack(push, 1)
class constants_t {
public:
	lock_float_t max_falling_speed;
	lock_float_t player_float_power;
	lock_float_t wind_speed;
	lock_float_t wind_speed_against;
	lock_float_t local_collision_for_net_player_max_divergence;
	lock_float_t player_drag;
	lock_float_t initial_jump_boost;
	lock_float_t control_mod_when_hurt;
	vec2_t<lock_float_t> lava_bounce_power;
	lock_float_t trampoline_bounce_power;
	lock_float_t bouncy_bounce_power;
	lock_float_t punched_knockback_default;
	lock_float_t parasol_grav_reduce_mod;
	lock_float_t under_water_gravity_mod;
	lock_float_t mars_gravity_mod;
	lock_float_t one_thousand;
	lock_float_t ghost_speed;
	lock_float_t water_levitation_time;
	lock_float_t punch_reload_time;
	lock_float_t delay_between_hack_reports_ms;
};
#pragma pack(pop)
