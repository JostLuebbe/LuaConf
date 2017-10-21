all:
	g++ -g script.cpp luaconf.cpp luaconf_demo.cpp -llua -ldl -o LuaConf
#	g++ -g script.cpp luaconf.cpp luaconf_demo.cpp -framework Lua -o LuaConf
