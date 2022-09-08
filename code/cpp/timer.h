

#ifndef _TIMER_ME_
#define _TIMER_ME_

#include<vector>
#include<queue>
//#include<chrono>
#include<ctime>

//单个定时器定义
class timer
{
    private:
        time_t start_time;                          //起始时间
        time_t end_time;                            //结束时间
        void* data;                                 //回调函数所需要的数据
        void* (*call_back)(void*);                  //回调函数
    public:
        timer(int time_ms,void* data,void* (*call_back)(void*));     //初始化函数  参数为 定时时长+回调函数
        void* run_call_back();                      //执行回调函数 
};





#endif