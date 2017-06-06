#ifndef LUACONF_LUACONF
#define LUACONF_LUACONF

#include <vector>

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
    void loadArgs(const char** args, int n);
    ~LuaConf();

    void reload();
private:
    std::vector<const char*> var_names;
    std::vector<luaVars> vars;
};

#endif
