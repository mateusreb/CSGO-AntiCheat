#pragma once

namespace ProtocolMgr
{
	ClientPtr pClient;

	void Init(ClientPtr Client)
	{
		pClient = Client;
	}

	template <typename T>
	void SendMsg(PROTOCOL_LIST protocol, T *pMsg, size_t bytes)
	{
		PACKET_HEADER header;
		uint32_t myseed = 0;
		XXHash32 myhash(myseed);
		myhash.add(pMsg, bytes);

		std::unique_ptr<PacketBuffer> m_OutBuffer(new PacketBuffer(sizeof(PACKET_HEADER) + bytes));

		header.protocol = protocol;
		header.length = bytes;
		header.checksum = myhash.hash();
		
		m_OutBuffer->Write((const char*)&header, sizeof(PACKET_HEADER));
		m_OutBuffer->Write((const char*)pMsg, bytes);

		printf("Send:\n");
		Helpers::enc((char*)&m_OutBuffer->m_Buffer[0], sizeof(PACKET_HEADER) + bytes);
		Helpers::enc((char*)&m_OutBuffer->m_Buffer[0], sizeof(PACKET_HEADER) + bytes);
		Helpers::EncryptData((unsigned char*)&m_OutBuffer->m_Buffer[0], sizeof(PACKET_HEADER) + bytes, 55);
		//Helpers::hexDump((unsigned char*)&m_OutBuffer->m_Buffer[0], sizeof(PACKET_HEADER) + bytes);
		pClient->Send((const void*)&m_OutBuffer->m_Buffer[0], sizeof(PACKET_HEADER) + bytes);
		m_OutBuffer.release();
	}

	void HandleMsg(PROTOCOL_LIST protocol, std::vector<uint8_t>m_Buffer, ClientID clientId)
	{
		switch (protocol)
		{
		case PROTOCOL_LIST::PROTOCOL_INIT:
		{
			PACKET_INIT* pInit = reinterpret_cast<PACKET_INIT*>(&m_Buffer[0]);
			//printf("Packet Recv: %i - %i - %i\n", pInit->pubKey, pInit->privKey, pInit->seed);
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