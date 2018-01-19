#pragma once

#include <fstream>
#include <stdio.h>

#include "LuaConf.h"

int main() {
	std::ofstream luaFile;
	luaFile.open("luaconf_demo.lua", std::ios::trunc);
	luaFile << "testVar1 = 42\n";
	luaFile << "testVar2 = \"foo\"\n";
	luaFile.close();

	LuaScript script;
	script.load("luaconf_demo.lua");
	printf("%d\n", (int)script.getNumber("testVar1"));
	printf("%s\n", script.getString("testVar2"));

	return 0;
}