#include "luaconf.h"
#include <fstream>
#include <iostream>

#define qprint(str) std::cout << str <<std::endl;

int main() {
    std::ofstream luaFile;
    luaFile.open("luaconf_demo.lua", std::ios::trunc);
    luaFile << "testVar1 = 42\n";
    luaFile << "testVar2 = \"foo\"\n";
    luaFile.close();
    LuaConf lc("luaconf_demo.lua");
    // Script sc("luaconf_demo.lua");
    const char* varNames[] = {"testVar1", /*"testVar2"*/};
    lc.loadArgs(varNames, 1);
    bool pass = true;

    float testVar1 = *lc.getFloatPtr("testVar1");
    char* testVar2 = lc.getStringPtr("testVar2");

    if(testVar1 == 42)
        std::cout << "Test 1 pass" << std::endl;
    else {
        pass = false;
        std::cout << "Test 1 failed" << std::endl;
    }
    if(strncmp(testVar2,"foo",3) == 0)
        std::cout << "Test 2 pass" << std::endl;
    else {
        pass = false;
        std::cout << "Test 2 failed" << std::endl;
    }
}
