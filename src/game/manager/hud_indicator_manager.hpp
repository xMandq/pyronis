#pragma once
#include <cstdint>

#pragma pack(push, 1)
class hud_indicator_manager_t {
public:
	void* vftable;
	std::uint8_t pad[24];
};
#pragma pack(pop)
