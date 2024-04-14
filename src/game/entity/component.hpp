#pragma once
#include <game/utils/boost.hpp>
#include <game/manager/variant_db.hpp>

#include <cstdint>
#include <string>

class entity_t;

#pragma pack(push, 1)
class entity_component_t {
public:
	virtual ~entity_component_t();
	virtual void on_add(entity_t* entity);
	virtual void on_remove();

	variant_t* get_var(const std::string& key_name) noexcept {
		return shared_db.get_var(key_name);
	}

	function_object_t* get_function(const std::string& key_name) noexcept {
		return shared_db.get_function(key_name);
	}

	boost_trackable_signal_t trackable_signal;
	std::string* name;
	entity_t* parent;
	variant_db_t shared_db;
};
#pragma pack(pop)

