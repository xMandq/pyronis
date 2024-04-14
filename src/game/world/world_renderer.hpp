#pragma once
#include <game/world/world_camera.hpp>

#include <cstdint>

class world_t;

#pragma pack(push, 1)
class world_renderer_t {
public:
	void* vftable;
	world_t* world;
	std::uint8_t pad1[136];
	world_camera_t camera; // 0x98


	// so much useless shit, cba to add rn
	//steam_manager 0x70
	//particle_system 0xf8
	//avatar_renderer 0x240
	//fish_list 0x2ea8
	//c_random 0x2ec8
	//robot_system 0x3988
	//robot_projectile_system 0x39a8
	//arrow_to_item_helper 0x39d8

};
#pragma pack(pop)
