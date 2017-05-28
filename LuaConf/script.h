#ifndef LUACONF_SCRIPT
#define LUACONF_SCRIPT

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

typedef enum {false, true} bool;

typedef struct {
    lua_State* state;
} luaFile;

luaFile* genLuaScript(const char* path);
void freeLuaScript(luaFile* L);
double getNumber(luaFile L, const char* var_name);
bool getBoolean(luaFile L, const char* var_name);
const char* getString(luaFile L, const char* var_name);


#endif // LUACONF_SCRIPT
