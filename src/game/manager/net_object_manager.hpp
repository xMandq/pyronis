#pragma once
#include <game/player/net_avatar.hpp>

#include <map>

#pragma pack(push, 1)
class net_object_manager_t {
public:
	void* vtable;
	std::map<std::int32_t, net_avatar_t*> players;
	std::uint8_t pad1[56];
};
#pragma pack(pop)
