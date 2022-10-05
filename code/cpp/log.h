

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
#include<iomanip>
#include<windows.h>
#include<direct.h>

#define WRITE_LOG(level,message) write_log_entity(level,message,__FILE__,__FUNCTION__,__LINE__)

enum log_level
{
    Logs    =   0,                                      //向日志文件输出 控制台绿色输出
    Error   =   1,                                      //红字输出
    Warn    =   2,                                      //黄字输出
    Info    =   3,                                      //白字输出
};

//日志函数
class Log
{
    private:
        std::ofstream out;
        std::string file_name; 
    public:
        Log();
        ~Log();
        //获取当前日期的字符串 例：2022_9_14
        std::string get_date_string();              
        //获取当前日期的字符串(详细) 例：2022:9:14
        std::string get_date_detail_string();      
        //文件夹检测(不存在则创建文件夹)
        bool check_folder(std::string name);
        //打开文件
        bool open_file(std::string name);           
        //设置控制台颜色
        void set_console_color(int n);              
        //输出颜色对照表
        void cout_console_color_table();  
        //log打印          
        void write_log_entity(log_level level,std::string message,const char* file,const char* fun,int line);
};

extern Log* logs;

#endif
