#pragma once

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <map>
#include <utility>
#include <string>
#include <assert.h>

class LuaScript {
public:
	LuaScript() {}

	void load(const char* path) {
		L = luaL_newstate();
		luaL_openlibs(L);
		if (luaL_loadfile(L, path) || lua_pcall(L, 0, 0, 0))
			printf("%s\n", lua_tostring(L, -1));
	}

	~LuaScript() {
		lua_close(L);
	}

	double getNumber(const char* varName) {
		lua_getglobal(L, varName);
		assert(lua_isnumber(L, -1));
		double value = lua_tonumber(L, -1);
		lua_remove(L, -1);
		return value;
	}

	bool getBoolean(const char* varName) {
		lua_getglobal(L, varName);
		assert(lua_isboolean(L, -1));
		int value = lua_toboolean(L, -1);
		lua_remove(L, -1);
		return value == 1 ? true : false;
	}

	const char* getString(const char* varName) {
		lua_getglobal(L, varName);
		assert(lua_isstring(L, -1));
		const char* value = lua_tostring(L, -1);
		lua_remove(L, -1);
		return value;
	}

	int getType(const char* varName) {
		lua_getglobal(L, varName);
		int t = lua_type(L, -1);
		lua_remove(L, -1);
		return t;
	}

private:
	lua_State* L;
};

class LuaConf {
public:
	LuaConf() {}
	LuaConf(const char* path) {
		this->path = path;
		script.load(path);
	}

	void loadArgs(const char** varNames, int n) {
		for (int i = 0; i < n; ++i) {
			luaVar lv;
			int type = script.getType(varNames[i]);
			if (type == LUA_TNUMBER) {
				lv.type = LUA_TNUMBER;
				lv.number = script.getNumber(varNames[i]);
			}
			else if (type == LUA_TBOOLEAN) {
				lv.type = LUA_TBOOLEAN;
				lv.boolean = script.getBoolean(varNames[i]);
			}
			else if (type == LUA_TSTRING) {
				lv.type = LUA_TSTRING;
				lv.string = const_cast<char*>(script.getString(varNames[i]));
			}

			luaVarMap[varNames[i]] = lv;
		}
	}

	void reload() {
		for (auto i = luaVarMap.begin(); i != luaVarMap.end(); ++i) {

		}
	}

	//TODO: template for int and double
	const double* LuaConf::getNumberPtr(const char* varName) {
		if (luaVarMap.find(varName) == luaVarMap.end()) {
			//TODO: add new luaVar
		}
		else {
			assert(luaVarMap[varName].type == LUA_TNUMBER);
		}
		return &luaVarMap[varName].number;
	}

	const bool* LuaConf::getBoolPtr(const char* varName) {
		if (luaVarMap.find(varName) == luaVarMap.end()) {
			//TODO: add new luaVar
		}
		else {
			assert(luaVarMap[varName].type == LUA_TBOOLEAN);
		}
		return &luaVarMap[varName].boolean;
	}

	const std::string* LuaConf::getStringPtr(const char* varName) {
		if (luaVarMap.find(varName) == luaVarMap.end()) {
			//TODO: add new luaVar
		}
		else {
			assert(luaVarMap[varName].type == LUA_TSTRING);
		}
		return &luaVarMap[varName].string;
	}

private:
	struct luaVar {
		luaVar() {}
		~luaVar() {}
		luaVar& operator =(const luaVar&) {}
		int type;
		union { //this is cool https://stackoverflow.com/a/13624921
			double number;
			bool boolean;
			std::string string;
			luaVar* list;
		};
	};

	LuaScript script;
	std::string path;
	std::map<std::string, luaVar> luaVarMap;
};