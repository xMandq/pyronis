#pragma once
#include <game/utils/math.hpp>

#include <list>

#pragma pack(push, 1)
class world_object_t {
public:
    void* vtable;
    vec2f_t pos;
    std::uint16_t item_id;
    std::uint8_t count;
    std::uint8_t flags;
    std::uint32_t object_id;
    std::uint32_t insert_timestamp;
    std::uint8_t pad1[20];
};

static_assert(sizeof(world_object_t) == 0x30);

struct world_object_map_t {
    void* vftable;
    std::uint8_t pad1[72];
    std::list<world_object_t> objects;
};
#pragma pack(pop)
