#pragma once

namespace ProtocolMgr
{
	void HandleMsg(IServer& server, void* pMsg, size_t bytes)
	{
		Helpers::RSADecryptBytes("pri.key", (byte*)&pMsg, sizeof(PACKET_HEADER) + sizeof(PACKET_AUTH));
		PACKET_HEADER header = Helpers::DeserializeProtocol(pMsg, bytes);
		switch (header.protocol)
		{
		case PROTOCOL_LIST::PROTOCOL_HANDSHAKE:
			PACKET_AUTH pAuth;
			if (Helpers::DeserializeMsg(header, &pAuth, pMsg, sizeof(PACKET_AUTH)))
			{				
				//printf("PROTOCOL_HANDSHAKE(%i %i %i)\n", pHandShake.user_id, pHandShake.user_index, pHandShake.user_level);
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