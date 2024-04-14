#pragma once
#include <game/world/world_tile_map.hpp>
#include <game/world/world_object_map.hpp>

#include <cstdint>
#include <string>

#pragma pack(push, 1)
class world_t {
public:
	void* vftable;
	std::uint8_t pad1[2];
	std::uint16_t version;
	std::uint8_t pad2[132];
	world_tile_map_t tile_map;
	world_object_map_t object_map;
	std::string name;
};
#pragma pack(pop)
