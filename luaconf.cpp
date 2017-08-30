#include "luaconf.h"

#include <cstdarg>

LuaConf::LuaConf(const char* path) {
    Script L(path);
}

LuaConf::~LuaConf() {

}

void LuaConf::loadArgs(const char** var_names, int n) {
    luaVar lv;
    for(int i = 1; i < n; ++i) {
        int type = L.getType(var_names[i]);
        if(type == NUMBER)
            lv.fp = L.getNumber(var_names[i]);
        else if(type == BOOLEAN)
            lv.boolean = L.getBoolean(var_names[i]);
        else if(type == STRING)
            lv.string = const_cast<char*>(L.getString(var_names[i]));
    var_map[var_names[i]] = std::make_pair(NUMBER, lv);
    }
}

void LuaConf::reload() {

}

float* LuaConf::getFloatPtr(const char* var_name) {
    if(var_map[var_name].first == NUMBER)
        return &var_map[var_name].second.fp;
    else
        printf("%s is not a number\n", var_name);
}

bool* LuaConf::getBooleanPtr(const char* var_name) {
    if(var_map[var_name].first == BOOLEAN)
        return &var_map[var_name].second.boolean;
    else
        printf("%s is not a boolean\n", var_name);
}

char* LuaConf::getStringPtr(const char* var_name) {
    if(var_map[var_name].first == STRING)
        return var_map[var_name].second.string;
    else
        printf("%s is not a string\n", var_name);
}
