#pragma once
#include <cstdint>

#pragma pack(push, 1)
class text_manager_t {
public:
	void* vftable;
	std::uint8_t pad1[40];
};
#pragma pack(pop)
