#pragma once

#define MAX_CLIENTS 64

enum class CLIENT_STATUS
{
	USER_UNAUTHENTICATED = 0,
	USER_AUTHENTICATION_FAILED = 1,
	USER_AUTHENTICATED = 2,
	USER_BANNED = 3,
	USER_CONNECTED = 4,
	USER_DISCONNECTED = 5,
	USER_QUITTED = 6
};

#pragma pack( push, 1 )

typedef struct _CLIENT_INFO
{
	uint32_t index;
	char guid[50];
	CLIENT_STATUS status;

	_CLIENT_INFO(void)
	{
		index = -1;
		memset(guid, 0, sizeof(guid));
		status = CLIENT_STATUS::USER_UNAUTHENTICATED;
	}
	_CLIENT_INFO(uint32_t _index, char* _guid, CLIENT_STATUS _status)
	{
		index = _index;
		memcpy(guid, _guid, sizeof(guid));
		status = _status;
	}
	_CLIENT_INFO(const _CLIENT_INFO& t)
	{
		index = t.index;
		memcpy(guid, t.guid, sizeof(guid));
		status = t.status;
	}
	_CLIENT_INFO& operator=(const _CLIENT_INFO& t)
	{
		index = t.index;
		memcpy(guid, t.guid, sizeof(guid));
		status = t.status;
		return *this;
	}
} CLIENT_INFO, * PCLIENT_INFO;

#pragma pack( pop )