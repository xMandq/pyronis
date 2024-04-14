#pragma once
#include <game/utils/boost.hpp>
#include <game/utils/variant.hpp>

#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <hash_map>
#include <string>

#pragma pack(push,1 )
class function_object_t {
public:
	boost_signal_t sig_function;
};

class variant_db_t {
public:
	virtual ~variant_db_t();

	function_object_t* get_function(const std::string& key_name) noexcept {
		for (const auto& [name, function] : function_data)
			if (name == key_name)
				return function;

		return nullptr;
	}

	variant_t* get_var(const std::string& key_name) noexcept {
		for (const auto& [name, variant] : data)
			if (name == key_name)
				return variant;

		return nullptr;
	}

	stdext::hash_map<std::string, variant_t*> data;
	stdext::hash_map<std::string, function_object_t*> function_data;
	decltype(data)::iterator next_itor;
};
#pragma pack(pop)
