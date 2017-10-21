#ifndef LUACONF_LUACONF
#define LUACONF_LUACONF

#include "script.h"

#include <map>
#include <utility>
#include <string>

union luaVar {
    float fp;
    bool boolean;
    char* string;
};

typedef struct luaVarHolder {
    int type;
    union luaVar lv;
} luaVarHolder;

class LuaConf {
public:
    LuaConf() {}
    LuaConf(const char* path);
    void loadArgs(const char** args, int n);
    ~LuaConf();

    void reload();
    float* getFloatPtr(const char* var_name);
    bool* getBooleanPtr(const char* var_name);
    char* getStringPtr(const char* var_name);
private:
    Script L;
    std::map<std::string, luaVarHolder> var_map;
};

#endif
