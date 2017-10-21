#include "script.h"

#include <stdlib.h>
#include <stdio.h>

Script::Script(const char* path) {
     lua_State* L = luaL_newstate();
     luaL_openlibs(L);
     if(luaL_loadfile(L, path) || lua_pcall(L,0,0,0))
         printf("%s\n", lua_tostring(L, -1));
     this->L = L;
 }

 Script::~Script() {
     //lua_close(L);
 }

 void stackdump_g(lua_State* l)
 {
     int i;
     int top = lua_gettop(l);

     printf("total in stack %d\n",top);

     for (i = 1; i <= top; i++)
     {  /* repeat for each level */
         int t = lua_type(l, i);
         switch (t) {
             case LUA_TSTRING:  /* strings */
                 printf("string: '%s'\n", lua_tostring(l, i));
                 break;
             case LUA_TBOOLEAN:  /* booleans */
                 printf("boolean %s\n",lua_toboolean(l, i) ? "true" : "false");
                 break;
             case LUA_TNUMBER:  /* numbers */
                 printf("number: %g\n", lua_tonumber(l, i));
                 break;
             default:  /* other values */
                 printf("%s\n", lua_typename(l, t));
                 break;
         }
         printf("  ");  /* put a separator */
     }
     printf("\n");  /* end the listing */
 }

 double Script::getNumber(const char* var_name) {
     lua_getglobal(L, var_name);
     if(!lua_isnumber(L, -1))
         printf("001: %s is not a number\n", var_name);
     double value = lua_tonumber(L,-1);
     lua_remove(L,-1);
     return value;
 }

 bool Script::getBoolean(const char* var_name) {
     lua_getglobal(L, var_name);
     if(!lua_isboolean(L, -1))
         printf("%s is not a boolean\n", var_name);
     int value = lua_toboolean(L, -1);
     lua_remove(L, -1);
     return value == 1 ? true : false;
}

const char* Script::getString(const char* var_name) {
    lua_getglobal(L, var_name);
    if(!lua_isstring(L, -1))
        printf("%s is not a string\n", var_name);
    const char* value = lua_tostring(L, -1);
    lua_remove(L, -1);
    return value;
}

int Script::getType(const char* var_name) {
    lua_getglobal(L, var_name);
    int t = lua_type(L, -1);
    lua_remove(L, -1);
    return t;
}
