#include "luaconf.h"
#include <fstream>
#include <iostream>

int main() {
    LuaConf lc("luaconf_demo.lua");
    std::ofstream luaFile;
    luaFile.open("luaconf_demo.lua", std::ios::trunc);
    luaFile << "testVar1 = 42\n";
    luaFile << "testVar2 = \"foo\"";
    luaFile.close();
    const char* varNames[] = {"testVar1", "testVar2"};
    lc.loadArgs(varNames, 2);
    bool pass = true;

    int testVar1 = *(int*)lc.getFloatPtr("testVar1");
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
