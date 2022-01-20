#pragma once

namespace ServerMgr
{
	ServerPtr pServer;

	void Start()
	{
		InitParams params;
		Initialize(params);
		
		ServerParams serverParams;
		serverParams.port = "24507";
		serverParams.maxConnections = 10;
		serverParams.timeoutSeconds = 240.0f;

		pServer = CreateServer(serverParams);

		pServer->OnConnect([&](const IServer& server, int32_t clientId)
		{

		});

		pServer->OnDisconnect([](IServer& server, ClientID clientId)
		{
				printf("Cliente Desconectado: %i\n", clientId);
		});

		pServer->OnReceiveData([](IServer& server, ClientID clientId, const void* data, size_t bytes)
		{
			ProtocolMgr::HandleMsg(server, (void*)data, bytes);
		});

		pServer->StartListening();

		while (!pServer->HasError())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	void Stop()
	{
		ShutDown();
	}

	//ShutDown();
}