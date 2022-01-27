#pragma once

class ClientManager
{
private:
	std::vector<CLIENT_INFO> m_clients { };
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