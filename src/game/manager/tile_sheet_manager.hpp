#pragma once
#include <cstdint>

#pragma pack(push, 1)
class tile_sheet_manager_t {
public:
	virtual ~tile_sheet_manager_t();

	std::uint8_t pad1[24];
};
#pragma pack(pop)
