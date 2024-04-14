#pragma once
#include <cstdint>
#include <vector>

enum class item_flag : std::uint16_t {
	none = 0x0,
	flippable = 0x1,
	editable = 0x2,
	seedless = 0x4,
	permanent = 0x8,
	dropless = 0x10,
	no_self = 0x20,
	no_shadow = 0x40,
	world_locked = 0x80,
	beta = 0x100,
	auto_pickup = 0x200,
	mod = 0x400,
	rand_grow = 0x800,
	public_ = 0x1000,
	foreground = 0x2000,
	holiday = 0x4000,
	untradeable = 0x8000
};

enum class item_flag2 : std::uint32_t {
	none = 0x0,
	robot_deadly = 0x1,
	robot_shoot_left = 0x2,
	robot_shoot_right = 0x4,
	robot_shoot_down = 0x8,
	robot_shoot_up = 0x10,
	robot_can_shoot = 0x20,
	robot_lava = 0x40,
	robot_pointy = 0x80,
	robot_shoot_deadly = 0x100,
	guild_item = 0x200,
	guild_flag = 0x400,
	starship_help = 0x800,
	starship_reactor = 0x1000,
	starship_viewscreen = 0x2000,
	supermod = 0x4000,
	tile_deadly_if_on = 0x8000,
	long_hand_item = 0x10000,
	gemless = 0x20000,
	transmutable = 0x40000,
	dungeon_item = 0x80000,
	pve_melee = 0x100000,
	pve_ranged = 0x200000,
	pve_auto_aim = 0x400000,
	one_in_world = 0x800000,
	only_for_world_owner = 0x1000000
};

enum class fx_flag : std::uint32_t {
	none = 0x0,
	multi_anim_start = 0x1,
	ping_pong_anim = 0x2,
	overlay_object = 0x4,
	offset_up = 0x8,
	dual_layer = 0x10,
	multi_anim2_start = 0x20,
	unk_0x40 = 0x40,
	use_skin_tint = 0x80,
	seed_tint_layer1 = 0x100,
	seed_tint_layer2 = 0x200,
	rainbow_tint_layer1 = 0x400,
	rainbow_tint_layer2 = 0x800,
	glow = 0x1000,
	no_arms = 0x2000,
	front_arm_punch = 0x4000,
	render_offhand = 0x8000,
	slowfall_object = 0x10000,
	replacement_sprite = 0x20000,
	orb_float = 0x40000,
	unk_0x80000 = 0x80000,
	render_fx_variant_version = 0x100000
};

enum class visual_effect_type : std::uint32_t {
	none = 0,
	flame_flick,
	smoking,
	glow_tint1,
	anim,
	bubbles,
	pet,
	pet_anim,
	no_arms,
	wavey,
	wavey_anim,
	both_arms,
	low_hair,
	under_face,
	skin_tint,
	mask,
	anim_mask,
	low_hair_mask,
	ghost,
	pulse,
	colorize,
	colorize_to_shirt,
	colorize_anim,
	high_face,
	high_face_anim,
	rainbow_shift,
	backfore,
	colorize_with_skin,
	no_render,
	spin,
	off_hand,
	winged,
	sink,
	darkness,
	light_source,
	light_if_on,
	discolor,
	step_spin,
	pet_colored,
	silkfoot,
	tilty,
	tilty_dark,
	next_frame_if_on,
	wobble,
	scroll,
	light_source_pulse,
	bubble_machine,
	very_low_hair,
	very_low_hair_ask
};

enum class tile_storage_type : std::uint32_t {
	single_frame_alone = 0,
	single_frame = 1,
	smart_edge = 2,
	smart_edge_horizontal = 3,
	smart_cling = 4,
	smart_outer = 5,
	random = 6,
	smart_edge_vertical = 7,
	smart_edge_horizontal_cave = 8,
	smart_cling2 = 9,
	smart_edge_diagonal = 10
};

enum class tile_collision_type : std::uint32_t {
	none = 0,
	solid = 1,
	jump_through = 2,
	gateway = 3,
	if_off = 4,
	one_way = 5,
	vip = 6,
	jump_down = 7,
	adventure = 8,
	if_on = 9,
	faction = 10,
	guild = 11,
	cloud = 12,
	friends_enterance = 13
};

enum class item_element_type : std::uint32_t {
	earth = 0,
	fire = 1,
	air = 2,
	wind = 2,
	water = 3,
	none = 4
};

enum class item_material_type : std::uint32_t {
	wood = 0,
	glass = 1,
	rock = 2,
	metal = 3
};

enum class body_part_type : std::uint32_t {
	hat = 0,
	shirt = 1,
	pants = 2,
	shoes = 3,
	face_item = 4,
	hand = 5,
	back = 6,
	hair = 7,
	chest_item = 8
};

enum class item_type : std::uint32_t {
	fist,
	wrench,
	user_door,
	lock,
	gems,
	treasure,
	deadly,
	trampoline,
	consumable,
	gateway,
	sign,
	sfx_with_extra_frame,
	boombox,
	door,
	platform,
	bedrock,
	lava,
	normal,
	background,
	seed,
	clothes,
	normal_with_extra_frame,
	background_sfx_with_extra_frame,
	back_boombox,
	bouncy,
	pointy,
	portal,
	checkpoint,
	musicnote,
	ice,
	unk_30,
	switcheroo,
	chest,
	mailbox,
	bulletin,
	pinata,
	dice,
	component,
	provider,
	lab,
	achievement,
	weather_machine,
	scoreboard,
	sungate,
	profile,
	deadly_if_on,
	heart_monitor,
	donation_box,
	toy_box,
	mannequin,
	camera,
	magic_egg,
	game_block,
	game_generator,
	cenonite,
	dressup,
	crystal,
	burglar,
	compactor,
	spotlight,
	wind,
	display_block,
	vending_machine,
	fish_tank,
	pet_fish,
	solar,
	forge,
	giving_tree,
	giving_tree_stump,
	steampunk,
	steam_lava_if_on,
	steam_organ,
	tamagotchi,
	sewing,
	flag,
	lobster_trap,
	art_canvas,
	battle_cage,
	pet_trainer,
	steam_engine,
	lock_bot,
	special_weather,
	spirit_storage,
	display_shelf,
	vip_door,
	challenge_timer,
	challenge_flag,
	fish_mount,
	portrait,
	special_weather2,
	fossil,
	fossil_prep,
	dna_machine,
	blaster,
	valhowla,
	chemsynth,
	chemtank,
	storage,
	oven,
	super_music,
	geiger_charger,
	adventure_reset,
	tomb_robber,
	faction,
	red_faction,
	green_faction,
	blue_faction,
	artifact,
	trampoline_momentum,
	fish_gotchi_tank,
	fishing_block,
	item_sucker,
	item_planter,
	robot,
	command,
	ticket,
	stats_block,
	field_node,
	ouija_board,
	architect_machine,
	starship,
	auto_delete,
	boombox2,
	auto_break,
	auto_harvest,
	auto_harvest_suck,
	lightning_if_on,
	phased_block,
	mud,
	root_cutting,
	password_storage,
	phased_block2,
	bomb,
	pve,
	infinity_weather,
	slime,
	acid,
	completionist,
	punch_toggle,
	anzu_block,
	feeding_block,
	krankens_block,
	friends_entrance,
	pearls
};

#pragma pack(push, 1)
class item_info_t {
public:
	std::uint32_t id;
	item_type type;
	item_material_type material;
	std::uint8_t pad1[4];
	std::string name;
	std::uint32_t texture_hash;
	std::uint8_t pad2[4];
	std::string texture_path;
	visual_effect_type visual_effect;
	std::int32_t cook_time;
	vec2_t<uint8_t> texture_pos;
	std::uint8_t pad3[2];
	tile_storage_type storage;
	std::uint32_t compute_value; // used in ItemInfo::ComputeSomething(), only has values on items 'stripey wallpaper' and 'totally harmless doll'
	tile_collision_type collision;
	std::uint16_t hits_to_destroy;
	item_flag flags;
	std::uint8_t pad4[68];
	std::uint32_t heal_time;
	body_part_type body_part;
	std::uint8_t seed_base;
	std::uint8_t seed_overlay;
	std::uint8_t tree_base;
	std::uint8_t tree_leaves;
	std::uint32_t seed_color;
	std::uint32_t seed_overlay_color;
	std::uint8_t pad5[4];
	std::uint32_t grow_time;
	std::uint8_t pad6[82];
	std::uint16_t rarity;
	std::uint8_t max_can_hold;
	std::uint8_t pad7[7];
	std::string extra_file;
	std::uint32_t extra_file_hash;
	std::uint32_t anim_ms;
	std::uint8_t pad8[40];
	std::uint32_t variant_item;
	std::uint8_t pad9[4];
	std::string pet_name;
	std::string pet_prefix;
	std::string pet_suffix;
	std::string pet_ability;
	std::uint8_t pad10[32];
	std::string unk_strs[8];
	std::uint8_t pad11[4];
	fx_flag fx_flags;
	std::string extra_options;
	std::string extra_options2;
	std::string texture2_path;
	std::uint8_t pad12[64];

	struct extra_slots_t {
		std::uint32_t body_part1;
		std::uint32_t body_part2;
		std::uint32_t body_part3;
		std::uint32_t body_part4;
		std::uint32_t body_part5;
		std::uint32_t body_part6;
		std::uint32_t body_part7;
		std::uint32_t body_part8;
		std::uint32_t body_part9;
	} extra_slots;

	std::uint32_t extra_slot_count;
	std::string punch_parameters;
	std::uint8_t last_pad[744];
};

static_assert(sizeof(item_info_t) == 0x700);

class item_info_manager_t {
public:
	item_info_t* get_item(std::uint32_t item_id) noexcept {
		if (item_id < items.size())
			return &items[item_id];

		return nullptr;
	}

	std::string get_item_name(std::uint32_t item_id) noexcept {
		if (item_info_t* item = get_item(item_id); item != nullptr)
			return item->name;

		return "(not found)";
	}

	void* vftable;
	std::vector<item_info_t> items;
	std::uint8_t pad1[24];
};
#pragma pack(pop)
