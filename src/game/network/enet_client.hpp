#pragma once
#include <game/utils/boost.hpp>

#include <cstdint>
#include <string>

#pragma pack(push, 1)
class enet_client_t {
public:
	void* vftable;
	boost_signal_t sig_unk1;
	boost_signal_t sig_unk2;
	boost_signal_t sig_unk3;
	boost_signal_t sig_unk4;
	std::uint8_t pad1[24];
	void* host; // 0xa0
	void* peer; // 0xa8
	std::uint32_t timed_out_timestamp;
	std::uint32_t unk0;
	std::uint32_t unk1;
	std::uint32_t unk2;
	std::string server_ip; // 0xc0
	std::uint32_t server_port; // 0xe0
	std::uint32_t unk3;
	std::int32_t token; // 0xe8
	std::int32_t user; // 0xec
	std::string door_id; // 0xf0
	std::int32_t lmode; // 0x110
	std::uint32_t unk4;
	std::string uuid_token; // 0x118
};
#pragma pack(pop)
