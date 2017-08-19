all:
	g++ -g script.cpp luaconf.cpp luaconf_demo.cpp -I/home/osboxes/lua-5.3.4/src/ -llua -ldl
