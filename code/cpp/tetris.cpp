
//此处为官方头文件

#include<iostream>
#include<windows.h>
#include<fstream>
#include<string>
#include<iterator>

//此处为扩展头文集
#include"expands/lua/lua.hpp"
#include"expands/json/json.h"

//此处为自定义头文件
#include"win.h"
#include"register.h"
#include"timer.h"
#include"log.h"
#include"graphics.h"

HINSTANCE hInstance;

/*
测试代码----暂时留存----抄来的
void readFileJson()
{
	Json::Reader reader;
	Json::Value root;
 
	//从文件中读取，保证当前文件有demo.json文件  
	std::ifstream in("configure/demo.json", std::ios::binary);
 
	if (!in.is_open())
	{
		std::cout << "Error opening file\n";
		return;
	}
 
	if (reader.parse(in, root))
	{
		//读取根节点信息  
		std::string name = root["name"].asString();
		int age = root["age"].asInt();
		std::string sex = root["sex"].asString();
 
		std::cout << "My name is " << name << std::endl;
		std::cout << "I'm " << age << " years old" << std::endl;
		std::cout << "I'm a " << sex << std::endl;
 
		//读取子节点信息  
		std::string friend_name = root["friends"]["friend_name"].asString();
		int friend_age = root["friends"]["friend_age"].asInt();
		std::string friend_sex = root["friends"]["friend_sex"].asString();
 
		std::cout << "My friend's name is " << friend_name << std::endl;
		std::cout << "My friend's sex is "<<friend_sex << std::endl;
		std::cout << "My friend is " << friend_age << " years old" << std::endl;
 
		//读取数组信息  
		std::cout << "Here's my hobby:" << std::endl;
		for (unsigned int i = 0; i < root["hobby"].size(); i++)
		{
			std::string ach = root["hobby"][i].asString();
			std::cout << ach << '\t';
		}
		std::cout << std::endl;
 
		std::cout << "Reading Complete!" << std::endl;
	}
	else
	{
		std::cout << "parse error\n" << std::endl;
	}
 
	in.close();
}
*/
void* call_back(void* T)
{
	int *t=(int*)T;
	std::cout<<*t<<std::endl;
	return nullptr;
}
int main()
{

    hInstance = GetModuleHandle(nullptr);
	
	AllocConsole();
    freopen("CONOUT$", "w", stdout);

	lua_State *lua = luaL_newstate(); 
    if(lua == nullptr)
    {
        return 0;
    }

    luaL_requiref(lua, "CFuncName", luaopen_C_Func_Name, 1);/*将C语言函数库注册到Lua环境中*/

	win->set_hInstance(hInstance, IMG_ICON_HUANXIONG);
    win->start_win(TEXT("俄罗斯方块"),200,100,1000,600);
    graphics->init(win->get_hwnd());

	luaL_openlibs(lua);
    luaL_dofile(lua, "../code/lua/debugPrint.lua");
	lua_close(lua);

	logs->LOG_WRITE(Logs,"这是一个测试 希望你能看到");

	for(int i=100;i<200;i++)
	{
		graphics->draw_pixel(i,100);
	}

	graphics->draw_line(200,100,0,0,true);

	int arr[3]={1000,2000,100};
	Timer_one* tim1=new Timer_one(1000,(void*)(arr),call_back);
	Timer_one* tim2=new Timer_one(2000,(void*)(arr+1),call_back);
	Timer_one* tim3=new Timer_one(100,(void*)(arr+2),call_back);
	timers->add_timer_one(tim1);
	timers->add_timer_one(tim2);
	timers->add_timer_one(tim3);

	while(true)
	{
		if(!win->loop_message())
		{
			break;
		}
		timers->update_timers();
	}
 
    return 0;
}