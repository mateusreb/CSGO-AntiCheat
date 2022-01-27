#include "Includes.h"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb); 
    return size * nmemb;
}

char* getMAC() {
	PIP_ADAPTER_INFO AdapterInfo;
	DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);
	char* mac_addr = (char*)malloc(18);

	AdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
	if (AdapterInfo == NULL) {
		printf("Error allocating memory needed to call GetAdaptersinfo\n");
		free(mac_addr);
		return NULL; // it is safe to call free(NULL)
	}

	// Make an initial call to GetAdaptersInfo to get the necessary size into the dwBufLen variable
	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW) {
		free(AdapterInfo);
		AdapterInfo = (IP_ADAPTER_INFO*)malloc(dwBufLen);
		if (AdapterInfo == NULL) {
			printf("Error allocating memory needed to call GetAdaptersinfo\n");
			free(mac_addr);
			return NULL;
		}
	}

	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) {
		// Contains pointer to current adapter info
		PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
		do {
			// technically should look at pAdapterInfo->AddressLength
			//   and not assume it is 6.
			sprintf(mac_addr, "%02X:%02X:%02X:%02X:%02X:%02X",
				pAdapterInfo->Address[0], pAdapterInfo->Address[1],
				pAdapterInfo->Address[2], pAdapterInfo->Address[3],
				pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
			printf("Address: %s, mac: %s\n", pAdapterInfo->IpAddressList.IpAddress.String, mac_addr);
			// print them all, return the last one.
			// return mac_addr;

			printf("\n");
			pAdapterInfo = pAdapterInfo->Next;
		} while (pAdapterInfo);
	}
	free(AdapterInfo);
	return mac_addr; // caller must free.
}


int main(int argc, char** argv)
{
	char priKey[128] = { 0 };
	char pubKey[128] = { 0 };
	char seed[1024] = { 0 };

	strcpy_s(priKey, "pri.key");
	strcpy_s(pubKey, "pub.key");
	strcpy_s(seed, "seed");

	//Helpers::GenerateRSAKey(1024, priKey, pubKey, seed);
	
	//RSA encryption and decryption 
	//char message[1024] = { 0 };
	//std::cout << "Origin Text:\t" << "Hello World!GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG" << std::endl << std::endl;
	//strcpy_s(message, "Hello World!");
	//std::string encryptedText = RSAEncryptString(pubKey, seed, message);//RSA encryption [Page]
	//std::cout << "Encrypted Text:\t" << encryptedText << std::endl << std::endl;
	//std::string decryptedText = RSADecryptString(priKey, encryptedText.c_str());//RSA decrypt 
	//std::cout << "Decrypted Text:\t" << decryptedText << std::endl << std::endl;

	InitParams params;
	Initialize(params);
	
	ClientParams clientParams;
	clientParams.address = "192.168.0.101";
	clientParams.port = "24507";
	clientParams.timeoutSeconds = 120.0;

	auto client = CreateClient(clientParams);			

	client->OnConnect([&](const IClient& client) 
	{
		printf("Cliente Conectado\n");		
	});

	client->OnDisconnect([](IClient& client)
	{
		printf("Cliente Desconectado\n");
	});

	client->OnReceiveData([](IClient& client, const void* data, size_t bytes)
	{
		printf("Recv Keys.\n");
		//HandleMsg((void*)data, bytes);
	});

	client->Connect();	
	ProtocolMgr::Init(client);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	PACKET_INIT init;


	memset(init.privKey, 0, 10);
	memset(init.pubKey, 0, 10);
	memset(init.seed, 0, 10);

	strcpy(init.privKey, "LprivKeye");
	strcpy(init.pubKey, "LpubKeyee");
	strcpy(init.seed, "Lseedeeee");

	//ProtocolMgr::SendMsg(PROTOCOL_LIST::PROTOCOL_INIT, &init, sizeof(PACKET_INIT));
	//strenc = 

	//std::vector<byte> enc(strenc.begin(), strenc.end());

	//strdec = Helpers::RSADecryptString("pri.key", strenc.c_str());
	//std::vector<byte> dec(strdec.begin(), strdec.end());
	//printf("Dec: %s\n", strdec.c_str());
	//Helpers::hexDump((unsigned char*)&dec[0], dec.size());
	//Helpers::hexDump((unsigned char*)&dec, 5);

	//printf("getCpuHash(): %X\n", getCpuHash());
	//printf("HWID1: %s\n", GetDriverSerial(0).c_str());
	//printf("HWID2: %s\n", GetDriverSerial(1).c_str());
	//printf("HWID3: %s\n", GetDriverSerial(2).c_str());
	//system("pause");

	//client->Send((void*)&m_OutBuffer->m_Buffer[0], sizeof(PACKET_HEADER) + sizeof(PACKET_INIT));
	//m_OutBuffer.release();
	//printf("TotalSize: %X\n", sizeof(PACKET_HEADER) + sizeof(PACKET_HANDSHAKE));
	//Helpers::Serealize(PROTOCOL_LIST::PROTOCOL_INIT, &buffer, &handshake_in, sizeof(PACKET_INIT));

	while (!client->HasError())
	{
		client->Send("'ABCDEFGHIJKLMN' + '”x19″x84″x04″x08'", 44);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	printf("Sock error!\n");
    /*CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) 
    {
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:95.0) Gecko/20100101 Firefox/95.0");
        curl_easy_setopt(curl, CURLOPT_URL, "https://gnu.terminalroot.com.br/ip.php");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        std::cout << readBuffer << std::endl;
    }*/
    return 0;
}