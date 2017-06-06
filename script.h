#ifndef LUACONF_SCRIPT
#define LUACONF_SCRIPT

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

enum {NUMBER, BOOLEAN, STRING};

class Script {
public:
    Script() {}
    Script(const char* path);
    ~Script();
    double getNumber(const char* var_name);
    bool getBoolean(const char* var_name);
    const char* getString(const char* var_name);
private:
    int getType(const char* var_name);
    lua_State* L;
};

#endif // LUACONF_SCRIPT
