#ifdef _INCLUDE_METAMOD_SOURCE_PLR
#endinput
#endif

#define _INCLUDE_METAMOD_SOURCE_PLR

#include <ISmmPlugin.h>

class PLR : 
	public ISmmPlugin
{
public:
    bool Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late);
    bool Unload(char *error, size_t maxlen);
    bool Pause(char *error, size_t maxlen);
    bool Unpause(char *error, size_t maxlen);
    void AllPluginsLoaded();
public:
    const char *GetAuthor();
    const char *GetName();
    const char *GetDescription();
    const char *GetURL();
    const char *GetLicense();
    const char *GetVersion();
    const char *GetDate();
    const char *GetLogTag();
public:
	void    Hook_GetPlayerLimits( int &minplayer, int &maxplayers, int &defaultmaxplayers );

};
