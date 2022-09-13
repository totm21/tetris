

#ifndef _LOG_ME_
#define _LOG_ME_

/*
    log打印
    也采取单例模式吧
    @auther:    程智
    @date:      2022.9.13
    @alter:     2022.9.13
*/

#include<iostream>
#include<fstream>
#include<string>

class log
{
    private:
        std::ofstream out;
        time_t last_update; 
    public:
        log();
        ~log();
}



#endif
