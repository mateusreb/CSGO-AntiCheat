#pragma once

enum class PROTOCOL_LIST
{
	PROTOCOL_UNKNOWN = 0x0000,
	PROTOCOL_INIT = 0xC001,
	PROTOCOL_AUTH = 0xC002,
	PROTOCOL_LOGIN = 0xC003,
	PROTOCOL_HEARTBEAT = 0xC004,
	PROTOCOL_DISCONNECT = 0xC005,
};

#pragma pack( push, 1 )

struct PACKET_HEADER
{
	PROTOCOL_LIST protocol;
	uint32_t length;
	uint32_t checksum;
	uint32_t tick;
};

struct PACKET_INIT
{
	char pubKey[128] = { 0 };
	char seed[1024] = { 0 };
};

struct PACKET_AUTH
{
	char steam_id[32];
	char guid[255];
};

#pragma pack( pop )
