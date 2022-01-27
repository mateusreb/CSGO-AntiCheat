#pragma once

namespace ProtocolMgr
{
	ServerPtr pServer;

	void Init(ServerPtr Server)
	{
		pServer = Server;
	}

	template <typename T>
	void SendMsg(PROTOCOL_LIST protocol, ClientID clientId, T *pMsg, size_t bytes)
	{
		void* pBuffer;
		Helpers::Serealize(protocol, &pBuffer, &pMsg, bytes);
		pServer->Send(clientId, (const void*)&pBuffer, sizeof(PACKET_HEADER) + bytes);
	}

	void HandleMsg(PROTOCOL_LIST protocol, std::vector<uint8_t>m_Buffer, ClientID clientId)
	{
		//Helpers::RSADecryptBytes("pri.key", (byte*)&m_Buffer[0], m_Buffer.size());
		//PACKET_HEADER header = Helpers::DeserializeProtocol(pMsg, bytes);
		//Helpers::RSAEncryptBytes("pub.key", "seed", (byte*)&m_Buffer[0], m_Buffer.size());
		switch (protocol)
		{
		case PROTOCOL_LIST::PROTOCOL_INIT:
			{
				PACKET_INIT *pInit = reinterpret_cast<PACKET_INIT*>(&m_Buffer[0]);
				printf("PROTOCOL_INIT\nPrivKey: %s \nPublicKey: %s \nSeed: %s\n", pInit->privKey, pInit->pubKey, pInit->seed);
				//if (Helpers::DeserializeMsg(header, &pInit, pMsg, sizeof(PACKET_AUTH)))
				//{
				//	printf("PROTOCOL_INIT:\nPrivKey: %s\nPublicKey: %s\nSeed: %s\n", pInit.privKey, pInit.pubKey, pInit.seed);
				//}
			}
			break;
		case PROTOCOL_LIST::PROTOCOL_LOGIN:
			printf("PROTOCOL_LOGIN\n");
			break;
		case PROTOCOL_LIST::PROTOCOL_HEARTBEAT:
			printf("PROTOCOL_HEARTBEAT\n");
			break;
		case PROTOCOL_LIST::PROTOCOL_DISCONNECT:
			printf("PROTOCOL_DISCONNECT\n");
			break;
		default:
			printf("PROTOCOL_UNKNOWN\n");
			break;
		}
	}
}