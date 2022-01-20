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
#include <randpool.h>
#include <rsa.h>
#include <hex.h>
#include <files.h>

using namespace CryptoPP;

#include "Scs/Scs.h"

using namespace Scs;

#include "xxhash/xxhash32.h"
#include "ClientMgr.h"
#include "Definitions.h"
#include "Helpers.h"
#include "ProtocolMgr.h"
#include "ServerMgr.h"
