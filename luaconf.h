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
#include <vector>

class LuaScript {
public:
	LuaScript() {}

	LuaScript(const std::string path) {
		load(path);
	}

	void load(const std::string path) {
		L = luaL_newstate();
		luaL_openlibs(L);
		if (luaL_loadfile(L, path.c_str()) || lua_pcall(L, 0, 0, 0))
			printf("%s\n", lua_tostring(L, -1));
	}

	~LuaScript() {
		lua_close(L);
	}

	double getNumber(const std::string varName) {
		lua_getglobal(L, varName.c_str());
		assert(lua_isnumber(L, -1));
		double value = lua_tonumber(L, -1);
		lua_remove(L, -1);
		return value;
	}

	bool getBoolean(const std::string varName) {
		lua_getglobal(L, varName.c_str());
		assert(lua_isboolean(L, -1));
		int value = lua_toboolean(L, -1);
		lua_remove(L, -1);
		return value == 1 ? true : false;
	}

	const std::string getString(const std::string varName) {
		lua_getglobal(L, varName.c_str());
		assert(lua_isstring(L, -1));
		const std::string value = lua_tostring(L, -1);
		lua_remove(L, -1);
		return value;
	}

	int getType(const std::string varName) {
		lua_getglobal(L, varName.c_str());
		int t = lua_type(L, -1);
		lua_remove(L, -1);
		return t;
	}

private:
	lua_State* L;
};

class LuaConf {
public:
	//LuaConf() {}
	LuaConf(const std::string path) {
		this->path = path;
		script.load(path);
	}

	void loadArgs(const std::string* varNames, int n) {
		for (int i = 0; i < n; ++i) {
			luaVar* lv = new luaVar();
			int type = script.getType(varNames[i]);

			switch (type) {
			case LUA_TNUMBER:
				lv->type = LUA_TNUMBER;
				lv->number = script.getNumber(varNames[i]);
				break;
			case LUA_TBOOLEAN:
				lv->type = LUA_TBOOLEAN;
				lv->boolean = script.getBoolean(varNames[i]);
				break;
			case LUA_TSTRING:
				lv->type = LUA_TSTRING;
				lv->string = script.getString(varNames[i]);
				break;
			}

			luaVarMap[varNames[i]] = lv;
		}
	}

	void reload() {
		script.load(path);
		int n = 0;
		std::vector<std::string> keys;
		for (auto i = luaVarMap.begin(); i != luaVarMap.end(); ++i) {
			keys.push_back(i->first.c_str());
			++n;
		}
		loadArgs(keys.data(), n);
	}

	//TODO: template for int and double
	const double* LuaConf::getNumberPtr(const std::string varName) {
		if (luaVarMap.find(varName) == luaVarMap.end()) {
			luaVarMap[varName] = new luaVar();
			luaVarMap[varName]->type = LUA_TNUMBER;
			luaVarMap[varName]->number = script.getNumber(varName);
		}
		else {
			assert(luaVarMap[varName]->type == LUA_TNUMBER);
		}
		return &luaVarMap[varName]->number;
	}

	const bool* LuaConf::getBoolPtr(const std::string varName) {
		if (luaVarMap.find(varName) == luaVarMap.end()) {
			luaVarMap[varName] = new luaVar();
			luaVarMap[varName]->type = LUA_TBOOLEAN;
			luaVarMap[varName]->boolean = script.getBoolean(varName);
		}
		else {
			assert(luaVarMap[varName]->type == LUA_TBOOLEAN);
		}
		return &luaVarMap[varName]->boolean;
	}

	const std::string* LuaConf::getStringPtr(const std::string varName) {
		if (luaVarMap.find(varName) == luaVarMap.end()) {
			luaVarMap[varName] = new luaVar();
			luaVarMap[varName]->type = LUA_TSTRING;
			luaVarMap[varName]->string = script.getString(varName);
		}
		else {
			assert(luaVarMap[varName]->type == LUA_TSTRING);
		}
		return &luaVarMap[varName]->string;
	}

private:
	struct luaVar {
		luaVar() {}
		~luaVar() {}
		luaVar& operator =(const luaVar&) { return *this; }
		int type;
		union {
			double number;
			bool boolean;
			std::string string;
			luaVar* list;
		};
	};

	LuaScript script;
	std::string path;
	std::map<std::string, luaVar*> luaVarMap;
};