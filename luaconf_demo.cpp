#pragma once

#include <fstream>
#include <stdio.h>

#include "LuaConf.h"

int main() {
	std::ofstream luaFile;
	luaFile.open("luaconf_demo.lua", std::ios::trunc);
	luaFile << "testVar1 = 42\n";
	luaFile << "testVar2 = \"foo\"\n";
	luaFile << "testVar3 = true\n";
	luaFile.close();

	printf("LuaScript Test\n");
	LuaScript script = LuaScript("luaconf_demo.lua");
	printf("%d\n", (int)script.getNumber("testVar1"));
	printf("%s\n", script.getString("testVar2").c_str());

	printf("\nLuaConf Test\n");
	LuaConf confScript("luaconf_demo.lua");
	std::string varNames[] = { "testVar1", "testVar2" };
	//confScript.loadArgs(varNames, 2);

	const double* numPtr = confScript.getNumberPtr("testVar1");
	printf("%f\n", *numPtr);
	//const std::string* str = confScript.getStringPtr("testVar2");
	//printf("%s\n", *str->c_str());

	//make changes to lua script
	luaFile.open("luaconf_demo.lua", std::ios::trunc);
	luaFile << "testVar1 = 1024\n";
	luaFile << "testVar2 = \"bar\"\n";
	luaFile << "testVar3 = nil\n";
	luaFile.close();

	script.load("luaconf_demo.lua");
	printf("%d\n", (int)script.getNumber("testVar1"));
	//printf("%s\n", script.getString("testVar2").c_str());

	confScript.reload();

	//printf("%f\n", *numPtr);

	return 0;
}