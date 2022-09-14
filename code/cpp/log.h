

#ifndef _LOG_ME_
#define _LOG_ME_

/*
    log打印
    也采取单例模式吧
    @auther:    程智
    @date:      2022.9.13
    @alter:     2022.9.14
*/

#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<chrono>

class Log
{
    private:
        std::ofstream out;
        std::string file_name; 
    public:
        Log();
        ~Log();
        std::string get_date_string();              //获取当前日期的字符串 例：2022:9:14
        bool file_open(std::string name);           //打开文件            
};



#endif
