#include "luaconf.h"

#include <cstdarg>

LuaConf::LuaConf(const char* path) {
    L = Script(path);
}

LuaConf::~LuaConf() {

}

void LuaConf::loadArgs(const char** var_names, int n) {

    for(int i = 0; i < n; ++i) {
        luaVarHolder lvh;
        int type = L.getType(var_names[i]);
        if(type == LUA_TNUMBER) {
            lvh.type = LUA_TNUMBER;
            lvh.lv.fp = L.getNumber(var_names[i]);
        }
        else if(type == LUA_TBOOLEAN) {
            lvh.type = LUA_TBOOLEAN;
            lvh.lv.boolean = L.getBoolean(var_names[i]);
        }
        else if(type == LUA_TSTRING) {
            lvh.type = LUA_TSTRING;
            lvh.lv.string = const_cast<char*>(L.getString(var_names[i]));
        }

        var_map[var_names[i]] = lvh;
    }

}

void LuaConf::reload() {

}

float* LuaConf::getFloatPtr(const char* var_name) {
    if(var_map[var_name].type == LUA_TNUMBER)
        return &var_map[var_name].lv.fp;
    else
        printf("004: %s is not a number\n", var_name);
    return NULL;
}

bool* LuaConf::getBooleanPtr(const char* var_name) {
    if(var_map[var_name].type == LUA_TBOOLEAN)
        return &var_map[var_name].lv.boolean;
    else
        printf("%s is not a boolean\n", var_name);
    return NULL;
}

char* LuaConf::getStringPtr(const char* var_name) {
    if(var_map[var_name].type == LUA_TSTRING)
        return var_map[var_name].lv.string;
    else
        printf("%s is not a string\n", var_name);
    return NULL;
}
