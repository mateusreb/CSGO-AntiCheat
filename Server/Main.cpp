#include "Includes.h"

int main(int argc, char** argv)
{
	/*ClientManager* pClientMgr = new ClientManager();

	for (int i = 0; i < 10; ++i)
	{
		std::stringstream guid_id;
		guid_id << "TEST_GUID_#" << i;
		pClientMgr->AddClient(i, (char*)guid_id.str().c_str(), CLIENT_STATUS::USER_AUTHENTICATED);
		printf("GUID: %s\n", guid_id.str().c_str());	
		CLIENT_INFO info;
		
		while (pClientMgr->GetNextClientUpdate(&info))
		{
			printf("USER: %i, %s, %i\n", info.index, info.guid, info.status);
		}
		pClientMgr->ResetClients();
	}	*/

	ServerMgr::Start();
	return 0;
}