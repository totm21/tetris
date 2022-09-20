
#include"log.h"

Log* logs=new Log();

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
    this->out.open("../data/log/"+name+".txt",std::ios::app);
    if(!this->out.is_open())
    {
        return false;
    }
    this->file_name=name;
    return true;
}

void Log::set_console_color(int n)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
	return;
}

void Log::cout_console_color_table()
{
    for(int i=0;i<256;i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
        std::cout<<std::setw(5)<<i;
        if((i+1)%16==0)
        {
            std::cout<<std::endl;
        }
    }
    return ;
}

void Log::log_write_entity(log_level level,std::string message,const char* file,const char* fun,int line)
{
    std::string data=this->get_date_string();
    if(data!=this->file_name)
    {
        this->file_open(data);
    }
    switch(level)
    {
        case Logs:
            this->out<<this->get_date_detail_string()<<" | "<<file<<" -> "<<fun<<" -> "<<line<<"----"<<message<<std::endl;
            this->set_console_color(2);
            break;
        case Error:
            this->set_console_color(4);
            break;
        case Warn:
            this->set_console_color(6);
            break;
        case Info:
            this->set_console_color(7);
            break;
    }
    std::cout<<this->get_date_detail_string()<<" | "<<file<<" -> "<<fun<<" -> "<<line<<"----"<<message<<std::endl;
    this->set_console_color(7);
    return ;
}

