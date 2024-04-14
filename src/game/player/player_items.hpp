#pragma once
#include <cstdint>
#include <list>

#pragma pack(push, 1)
struct inventory_item_t {
	std::uint16_t item_id;
	std::uint8_t count;
	std::uint8_t flags;
};

class player_items_t {
public:
	void* vftable;
	std::uint16_t clothes[12];
	std::list<inventory_item_t> items; // 0x20
	std::uint16_t quick_slot1; // 0x30
	std::uint16_t quick_slot2; // 0x32
	std::uint16_t quick_slot3; // 0x34
	std::uint16_t quick_slot4; // 0x36
	std::uint32_t backpack_size; // 0x38
	std::uint8_t pad1[4];
	std::list<inventory_item_t> filtered_items; // 0x40
	std::uint8_t pad2[72];
	std::uint16_t selected_item; // 0x98
	std::uint8_t pad3[6];
	std::int32_t gems; // 0xa0
	std::uint8_t pad4[12];
	std::int32_t gems_collected; // 0xb0
};
#pragma pack(pop)
