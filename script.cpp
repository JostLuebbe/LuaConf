#include "script.h"

#include <stdlib.h>
#include <stdio.h>

Script::Script(const char* path) {
    L = luaL_newstate();
	luaL_openlibs(L);
	if(luaL_loadfile(L, path) || lua_pcall(L,0,0,0))
		printf("%s\n", lua_tostring(L, -1));
}
