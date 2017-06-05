#ifndef LUACONF_LUACONF
#define LUACONF_LUACONF

#include "script.h"

union luaVars {
    int integer;
    bool boolean;
    const char* string;
};

class LuaConf {
public:
    LuaConf() {}
    LuaConf(const char* path);
    void loadArgs(const char** args);
    ~LuaConf();

    void reload();
private:
    
};

#endif
