/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod SQLite Extension
 * Copyright (C) 2004-2008 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#include <sourcemod_version.h>
#include "extension.h"


 /**
  * @file extension.cpp
  * @brief Implement extension code here.
  */

MSRProtectExt g_MSRProtect;		/**< Global singleton for extension's main interface */

SMEXT_LINK(&g_MSRProtect);

bool MSRProtectExt::SDK_OnLoad(char* error, size_t maxlength, bool late)
{
	return true;
}

void MSRProtectExt::SDK_OnUnload()
{
	
}

const char* MSRProtectExt::GetExtensionVerString()
{
	return SOURCEMOD_VERSION;
}

const char* MSRProtectExt::GetExtensionDateString()
{
	return SOURCEMOD_BUILD_TIME;
}

size_t UTIL_Format(char* buffer, size_t maxlength, const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	size_t len = vsnprintf(buffer, maxlength, fmt, ap);
	va_end(ap);

	if (len >= maxlength)
	{
		buffer[maxlength - 1] = '\0';
		return (maxlength - 1);
	}
	else
	{
		return len;
	}
}


cell_t SquareNumber(IPluginContext* pContext, const cell_t* params)
{
	cell_t number = params[1];
	return number * number;
}

const sp_nativeinfo_t MyNatives[] =
{
	{ "SquareNumber" , SquareNumber } ,
	 { NULL ,			 NULL } ,
};

void MSRProtectExt::SDK_OnAllLoaded()
{
	sharesys->AddNatives(myself, MyNatives);
}