

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

#define LOG_WRITE(level,message) log_write_entity(level,message,__FILE__,__FUNCTION__,__LINE__)

enum log_level
{
    log = 0,                                       //向日志文件输出
    error = 1,                                     //红字输出
    waring = 2,                                    //黄字输出
    info = 3,                                      //白字输出
};

class Log
{
    private:
        std::ofstream out;
        std::string file_name; 
    public:
        Log();
        ~Log();
        std::string get_date_string();              //获取当前日期的字符串 例：2022_9_14
        std::string get_date_detail_string();       //获取当前日期的字符串(详细) 例：2022:9:14
        bool file_open(std::string name);           //打开文件
        void log_write_entity(log_level level,std::string message,const char* file,const char* fun,int line);
        void log_write_entity_log(log_level level,std::string message,const char* file,const char* fun,int line);          
};



#endif
