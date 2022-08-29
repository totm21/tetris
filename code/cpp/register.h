#ifndef REGISTER_ME
#define REGISTER_ME
/*
    C函数注册给lua
    @auther:    程智
    @date:      2022.7.3
    @alter:     2022.7.3
*/

#include "expands/lua/lua.hpp"

/*所要调用的函数格式*/ //标准格式    这玩意儿是变量???
extern int C_Func_Child(lua_State* L);

/*创建一个新库*/  //标准格式
extern int luaopen_C_Func_Name(lua_State* L);





#endif