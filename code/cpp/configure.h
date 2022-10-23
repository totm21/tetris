
#ifndef _CONFIGURE_ME_
#define _CONFIGURE_ME_

#include<iostream>
#include<fstream>
#include<vector>

#include"expands/json/json.h"

class mb_node
{
    public:
        int id;
        void* data;     
};

class mb_data
{
    public:
        std::vector<char> type;      //表头类型
        std::vector<mb_node> data;


};

void readFileJson(std::string file);



#endif

