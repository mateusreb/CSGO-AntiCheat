#pragma once

#include <queue>
#include <bitset>
#include <array>

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

enum PROTOCOL_LIST
{
	PROTOCOL_UNKNOWN = 0x0000,
	PROTOCOL_HANDSHAKE = 0xC001,
	PROTOCOL_LOGIN = 0xC002,
	PROTOCOL_HEARTBEAT = 0xC003,
	PROTOCOL_DISCONNECT = 0xC004
};

struct PACKET_HEADER
{
	PROTOCOL_LIST protocol;
	uint32_t length;
	uint32_t checksum;
};

struct PACKET_INIT
{
	char steam_id[32];
};

struct PACKET_AUTH
{
	char steam_id[32];
	char guid[255];
};

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

class ClientManager
{
private:
	std::vector<CLIENT_INFO> m_clients{};
	uint32_t GetNextUserUpdateIdx = 0;

public:
	void AddClient(uint32_t index, char guid[32], CLIENT_STATUS status)
	{
		m_clients.push_back({ index, guid, status });
	}

	void RemoveClientByIndex(uint32_t index)
	{	
		for (uint32_t user_index = 0; user_index < (uint32_t)m_clients.size(); ++user_index)
		{
			if (m_clients[user_index].index == index)
			{
				m_clients[user_index].status = CLIENT_STATUS::USER_DISCONNECTED;
			}
		}
	}

	void RemoveClientByGuid(char guid[32])
	{
		for (uint32_t user_index = 0; user_index < (uint32_t)m_clients.size(); ++user_index)
		{
			if (!strcmp(m_clients[user_index].guid, guid))
			{
				m_clients[user_index].status = CLIENT_STATUS::USER_DISCONNECTED;
			}
		}
	}

	void UpdateClientStatusByGuid(char guid[32], CLIENT_STATUS status)
	{
		for (uint32_t user_index = 0; user_index < (uint32_t)m_clients.size(); ++user_index)
		{
			if (!strcmp(m_clients[user_index].guid, guid))
			{
				m_clients[user_index].status = status;
			}
		}
	}

	void UpdateClientStatusByIndex(uint32_t index, CLIENT_STATUS status)
	{
		for (uint32_t user_index = 0; user_index < (uint32_t)m_clients.size(); ++user_index)
		{
			if (m_clients[user_index].index == index)
			{
				m_clients[user_index].status = status;
			}
		}
	}

	bool GetClientInfoByGuid(char guid[32], PCLIENT_INFO info)
	{
		for (auto& Client : m_clients)
		{
			if (!strcmp(Client.guid, guid))
			{
				*info = Client;
				return true;
			}
		}
		return false;
	}

	uint32_t GetNextClientUpdate(PCLIENT_INFO info)
	{
		if (GetNextUserUpdateIdx < m_clients.size())
		{
			*info = m_clients[GetNextUserUpdateIdx];
			GetNextUserUpdateIdx++;
			return GetNextUserUpdateIdx;
		}
		else
		{
			return GetNextUserUpdateIdx = 0;
		}		
	}

	void ResetClients()
	{
		m_clients.clear();
	}

};