#ifndef LUACONF_SCRIPT
#define LUACONF_SCRIPT

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

typedef enum {false, true} bool;

typedef struct {
    lua_State* L;
} luaFile;



#endif // LUACONF_SCRIPT
