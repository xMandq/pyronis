#pragma once
#include <cstdint>
#include <string>

enum class tile_extra_type : std::uint8_t {
	none,
	door,
	sign,
	lock,
	tree,
	unk_5, // itemtype 30
	mailbox,
	bulletin,
	dice,
	provider,
	achievement_block,
	heart_monitor,
	donation_box,
	toy_box,
	mannequin,
	magic_egg,
	game_block,
	game_generator,
	xenonite,
	dressup,
	crystal,
	burglar,
	spotlight,
	display_block,
	vending_machine,
	fishtank,
	solar,
	forge,
	giving_tree,
	giving_tree_stump,
	steam_organ,
	silkworm,
	sewing_machine,
	flag,
	lobster_trap,
	art_canvas,
	battle_cage,
	pet_trainer,
	steam_engine,
	lock_bot,
	background_weather,
	spirit_storage,
	data_bedrock,
	display_shelf,
	vip_timer,
	challenge_timer,
	unk_46,
	fish_mount,
	portrait,
	stuff_weather,
	fossil_prep,
	dna_machine,
	trickster,
	chemtank,
	storage,
	oven,
	super_music,
	geiger_charger,
	adventure_reset,
	tomb_robber,
	faction,
	training_fish_port,
	item_sucker,
	robot,
	ticket,
	guild_item,
	stats_block,
	field_node,
	ouija_board,
	auto_break,
	auto_harvest,
	auto_harvest_sucker,
	lightning_if_on,
	phased_block,
	safe_vault,
	phased_block2,
	pve_npc,
	infinity_weather,
	completionist,
	feeding_block,
	krankens_block,
	friends_entrance
};

#pragma pack(push, 1)
class tile_extra_t {
public:
	void* vftable;
	tile_extra_type type; // 0x8
	std::uint8_t pad1[3];

	union { // 0xc
		std::int32_t item_price; // vending price, negative: items per wl, positive: wls per item
		std::uint32_t owner; // lock owner
	};

	std::string unk1; // 0x10
	std::string label; // 0x30
	std::string unk2; // 0x50

	union { // 0x70
		std::uint32_t item_id; // vending item
		std::uint32_t last_updated_timestamp; // for seeds
	};

	std::uint32_t growth; // 0x74
	std::uint8_t fruit_count; // 0x78
	std::uint8_t pad2[31];
	std::vector<std::uint32_t> access_list; // 0x98

	// more
};
#pragma pack(pop)
