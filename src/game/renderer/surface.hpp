#pragma once
#include <game/utils/boost.hpp>
#include <game/utils/math.hpp>

#include <string>

enum class texture_type {
	default_,
	gui,
	not_owner,
	no_smoothing
};

enum class blending_mode_type {
	normal,
	additive,
	premultiplied_alpha,
	multiply,
	darken
};

enum class texture_creation_method_type {
	none,
	file,
	memory,
	blank
};

#pragma pack(push, 1)
class surface_t { // im not sure if correct offsets, i just copied from proton
public:
	virtual ~surface_t();
	// more virtual funcs

	boost_trackable_signal_t trackable_signal;
	std::uint16_t texture_id;
	std::uint8_t pad1[2];
	vec2i_t texture_size;
	vec2i_t original_size;
	bool uses_alpha;
	texture_type texture_type;
	blending_mode_type blending_mode;
	std::int32_t mip_map_count;
	std::uint32_t frame_buffer;
	std::int32_t memory_used;
	std::string texture_loaded;
	bool create_mip_maps_if_needed;
	texture_creation_method_type texture_creation_method;
	bool smoothing;
	bool add_base_path;
};
#pragma pack(pop)
