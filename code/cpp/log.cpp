
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
    return std::to_string(1900 + now->tm_year) + ":" + std::to_string(1 + now->tm_mon) + ":" + std::to_string(now->tm_mday);
}

bool Log::file_open(std::string name)
{
    if(this->file_name!="")
    {
        this->out.close();
        this->file_name="";
    }
    this->out.open(name,std::ios::out);
    if(!this->out.is_open())
    {
        return false;
    }
    this->file_name=name;
    return true;
}