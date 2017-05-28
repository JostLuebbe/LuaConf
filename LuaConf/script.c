#include "script.h"

#include <stdlib.h>
#include <stdio.h>

luaFile* genLuaScript(const char* path) {
    luaFile* L = (luaFile*)malloc(sizeof(luaFile));
    L->state = luaL_newstate();
	luaL_openlibs(L->state);
	if(luaL_loadfile(L->state, path) || lua_pcall(L->state,0,0,0))
		printf("%s\n", lua_tostring(L->state, -1));
}
