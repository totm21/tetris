
//此处为官方头文件
#include<iostream>
#include<windows.h>
#include<fstream>
#include<string>

//此处为扩展头文集
#include"expands/json/json.h"

//此处为自定义头文件
#include"win.h"

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

int main()
{
    hInstance = GetModuleHandle(nullptr);
	
	AllocConsole();
    freopen("CONOUT$", "w", stdout);

	Win win(hInstance);
    win.start_win(TEXT("俄罗斯方块"),200,100,1000,600);
    
    
    return 0;
}