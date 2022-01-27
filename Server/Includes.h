#pragma once

#include <iostream>
#include <chrono>
#include <atomic>
#include <thread>
#include <vector>
#include <cstring>
#include <assert.h>
#include <stdexcept>
#include <sstream>
//#include <randpool.h>
//#include <rsa.h>
//#include <hex.h>
//#include <files.h>
#include <queue>
#include <bitset>
#include <array>

//using namespace CryptoPP;

#include "Scs/Scs.h"

using namespace Scs;

#include "aes256/AES.h"
#include "xxhash/xxhash32.h"
#include "Definitions.h"
#include "ClientMgr.h"
#include "Packets.h"
#include "PacketBuffer.h"
#include "Helpers.h"
#include "ProtocolMgr.h"
#include "ServerMgr.h"
