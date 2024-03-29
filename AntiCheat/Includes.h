#pragma once

#define CURL_STATICLIB
#include <iostream>
#include <curl\curl.h>
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <atomic>
#include <thread>
#include <vector>
#include <cstring>
#include <assert.h>
#include <stdexcept>
#include <xxhash/xxhash32.h>
//#include <randpool.h>
//#include <rsa.h>
//#include <hex.h>
//#include <files.h>
#include <Iphlpapi.h>

#pragma comment(lib, "iphlpapi.lib")

#include "Scs/Scs.h"

using namespace Scs;

#include "aes256/AES.h"
#include "Packets.h"
#include "Helpers.h"
#include "HWID.h"
#include "PacketBuffer.h"
#include "ProtocolMgr.h"
#include "ClientMgr.h"



