
#include"log.h"

Log* logs=new Log();

Log::Log()
{
    this->file_name="";
    this->open_file(this->get_date_string());
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

bool Log::check_folder(std::string folder)
{
    if (0 != access(folder.c_str(), 0))
    {
        if(mkdir(folder.c_str()) == -1)   // 返回 0 表示创建成功，-1 表示失败
        {
            return false;
        }
    }
    return true;
}

bool Log::open_file(std::string name)
{
    if(this->file_name!="")
    {
        this->out.close();
        this->file_name="";
    }
    if(this->check_folder("log")==false)
    {
        this->WRITE_LOG(Error,"文件夹不存在(尝试创建失败)");
        return false;
    }
    this->out.open("log/"+name+".txt",std::ios::app);
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

void Log::write_log_entity(log_level level,std::string message,const char* file,const char* fun,int line)
{
    std::string data=this->get_date_string();
    if(data!=this->file_name)
    {
        this->open_file(data);
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

