/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod Sample Extension
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

#include "extension.h"
#include "interface.h"
#include "engine/iserverplugin.h"
#include "eiface.h"

#include "icommandline.h"

PLR g_PLR;

PLUGIN_EXPOSE(PLR, g_PLR);

IServerGameClients	*gameclients = NULL;

int g_iMaxPlayers;

SH_DECL_HOOK3_void( IServerGameClients, GetPlayerLimits, const, 0, int &, int &, int & );

bool PLR::Load(	PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late )
{
	PLUGIN_SAVEVARS();
	GET_V_IFACE_CURRENT(GetServerFactory, gameclients, IServerGameClients, INTERFACEVERSION_SERVERGAMECLIENTS);

	META_LOG(g_PLAPI, "Starting plugin.");

	if( !gameclients )
	{
		return false;
	}

	const char *pszCmdLineMax;
	if( !CommandLine()->CheckParm("-maxplayers", &pszCmdLineMax )
		&& !CommandLine()->CheckParm("+maxplayers", &pszCmdLineMax ) )
	{
		return false;
	}

	g_iMaxPlayers = clamp( atoi( pszCmdLineMax ), 1, ABSOLUTE_PLAYER_LIMIT );

	SH_ADD_HOOK( IServerGameClients, GetPlayerLimits, gameclients, SH_MEMBER(this, &PLR::Hook_GetPlayerLimits), false );

	return true;
}

bool PLR::Unload( char *error, size_t maxlen )
{
	SH_REMOVE_HOOK( IServerGameClients, GetPlayerLimits, gameclients, SH_MEMBER(this, &PLR::Hook_GetPlayerLimits), false );

	return true;
}

void PLR::Hook_GetPlayerLimits( int &minplayers, int &maxplayers, int &defaultmaxplayers )
{
	minplayers = 1;
	maxplayers = ABSOLUTE_PLAYER_LIMIT;
	defaultmaxplayers = g_iMaxPlayers;

	RETURN_META( MRES_SUPERCEDE );
}

bool PLR::Pause(char *error, size_t maxlen)
{
    return true;
}

bool PLR::Unpause(char *error, size_t maxlen)
{
    return true;
}

void PLR::AllPluginsLoaded()
{
}

const char *PLR::GetLicense()
{
	return "GPL";
}

const char *PLR::GetVersion()
{
	return "1.0.0";
}

const char *PLR::GetDate()
{
	return __DATE__;
}

const char *PLR::GetLogTag()
{
	return "PLR";
}

const char *PLR::GetAuthor()
{
	return "Drunken_F00l, Bottiger, maxime1907";
}

const char *PLR::GetDescription()
{
	return "Set any number from 1 to 255 for your srcds +maxplayers setting";
}

const char *PLR::GetName()
{
	return "Player Limit Remover";
}

const char *PLR::GetURL()
{
	return "http://www.SourceMod.net/";
}
