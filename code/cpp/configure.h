
#ifndef _CONFIGURE_ME_
#define _CONFIGURE_ME_

#include<iostream>
#include<fstream>
#include<vector>

#include"expands/json/json.h"

//单条数据
class mb_node
{
    public:
        int id;
        std::vector<void*> data;
};

//单个表数据
class mb_data
{
    public:
        std::string name;
        std::vector<char> type;      //表头类型
        std::vector<mb_node> data;

};

void readFileJson(std::string file);



#endif

