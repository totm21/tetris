
#include"log.h"

Log::Log()
{
    this->file_name="";
    this->file_open(this->get_date_string());
}

Log::~Log()
{
    if(this->file_name!="")
    {
        this->out.close();
        this->file_name="";
    }
}

std::string Log::get_date_string()
{
    std::time_t t=std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm* now=localtime(&t);
    return std::to_string(1900 + now->tm_year) + "_" + std::to_string(1 + now->tm_mon) + "_" + std::to_string(now->tm_mday);
}

std::string Log::get_date_detail_string()
{
    std::time_t t=std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm* now=localtime(&t);
    return std::to_string(1900 + now->tm_year) + "-" + std::to_string(1 + now->tm_mon) + "-" + std::to_string(now->tm_mday) + " " + std::to_string(now->tm_hour) + ":" +std::to_string(now->tm_min)+ ":" +std::to_string(now->tm_sec);
}

bool Log::file_open(std::string name)
{
    if(this->file_name!="")
    {
        this->out.close();
        this->file_name="";
    }
    this->out.open("../data/log/"+name,std::ios::out);
    if(!this->out.is_open())
    {
        return false;
    }
    this->file_name=name;
    return true;
}

void Log::log_write_entity(log_level level,std::string message,const char* file,const char* fun,int line)
{
    std::string data=this->get_date_string();
    switch(level)
    {
        case log:
            this->out<<this->get_date_detail_string()<<'|'<<file<<"->"<<fun<<"->"<<line<<"----"<<message<<std::endl;
    }
    return ;
}