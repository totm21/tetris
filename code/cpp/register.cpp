#include"register.h"

/*定义函数表*/   //标准格式

/*所要调用的函数格式*/ //标准格式
int C_Func_Child(lua_State* L)
{
	printf("it's standard\n");
	return 0;
}

/*创建一个新库*/  //标准格式
int luaopen_C_Func_Name(lua_State* L) {
	
	/*创建一个标准表*/ 
	luaL_Reg C_Fun_Table[] = {
		{"C_Func_Child",C_Func_Child},
		{NULL,NULL}
	};

	luaL_newlib(L, C_Fun_Table);
	return 1;
}