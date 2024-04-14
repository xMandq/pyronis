#pragma once
#include <game/entity/component.hpp>
#include <game/manager/variant_db.hpp>

#include <cstdint>
#include <string>
#include <list>

#pragma pack(push, 1)
class entity_t {
public:
    virtual ~entity_t();

    entity_t* get_entity_by_name(const std::string& name) noexcept {
        auto it = std::find_if(children.begin(), children.end(),
            [&](entity_t* entity) {
                return entity->name == name;
            });

        if (it != children.end())
            return *it;

        return nullptr;
    }

    entity_component_t* get_component_by_name(const std::string& name) noexcept {
        auto it = std::find_if(components.begin(), components.end(),
            [&](entity_component_t* component) {
                return *component->name == name;
            });

        if (it != components.end())
            return *it;

        return nullptr;
    }

    variant_t* get_var(const std::string& key_name) noexcept {
        return shared_db.get_var(key_name);
    }

    function_object_t* get_function(const std::string& key_name) noexcept {
        return shared_db.get_function(key_name);
    }

    boost_trackable_signal_t trackable_signal;
    boost_signal_t sig_on_removed;
    std::string name;
    std::list<entity_t*> children;
    std::uint8_t pad2[80];
    std::list<entity_component_t*> components;
    std::uint8_t pad3[80];
    variant_db_t shared_db;
    entity_t* parent;
    bool tagged_for_deletion;
};
#pragma pack(pop)

