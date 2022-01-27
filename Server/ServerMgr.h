#pragma once

namespace ServerMgr
{
	ServerPtr pServer;

	bool Start()
	{
		InitParams params;
		Initialize(params);
		
		ServerParams serverParams;
		serverParams.port = "24507";
		serverParams.maxConnections = 64;
		serverParams.timeoutSeconds = 240.0f;

		pServer = CreateServer(serverParams);
		if (pServer)
		{
			ProtocolMgr::Init(pServer);
		}
		else
		{
			return false;
		}

		pServer->OnConnect([&](const IServer& server, ClientID clientId)
		{
				printf("Cliente Conectado: %i\n", clientId);
		});

		pServer->OnDisconnect([](IServer& server, ClientID clientId)
		{
				printf("Cliente Desconectado: %i\n", clientId);
		});
		
		pServer->OnReceiveData([](IServer& server, ClientID clientId, const void* data, size_t bytes)
		{
				if (bytes > sizeof(PACKET_HEADER))
				{
					Helpers::DecryptData((unsigned char*)data, bytes, 55);
					Helpers::dec((char*)data, bytes);
					Helpers::dec((char*)data, bytes);

					PACKET_HEADER header;
					std::unique_ptr<PacketBuffer>m_InBuffer(new PacketBuffer(bytes));
					std::vector<uint8_t> m_Buffer(bytes, 0);

					m_InBuffer->Write(data, bytes);
					m_InBuffer->Read(&header, sizeof(PACKET_HEADER));
					m_InBuffer->Read(&m_Buffer[0], bytes - sizeof(PACKET_HEADER));

					uint32_t myseed = 0;
					XXHash32 myhash(myseed);
					myhash.add(&m_Buffer[0], bytes - sizeof(PACKET_HEADER));

					printf("Header: %X %X [%X - %X]\n", header.protocol, header.length, header.checksum, myhash.hash());
					if (header.checksum == myhash.hash())
					{
						ProtocolMgr::HandleMsg(header.protocol, m_Buffer, clientId);
					}
					m_InBuffer.release();
				}
				else
				{
					server.DisconnectClient(clientId);
				}
		});

		pServer->StartListening();

		//ProtocolMgr::SendMsg(PROTOCOL_LIST::PROTOCOL_INIT, 1, &pInit, sizeof(PACKET_INIT));
		
		while (!pServer->HasError())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		return false;
	}

	void Stop()
	{
		ShutDown();
	}

	//ShutDown();
}