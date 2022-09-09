

#ifndef _TIMER_ME_
#define _TIMER_ME_

#include<vector>
#include<queue>
//#include<chrono>
#include<ctime>

//单个定时器定义
class timer_one
{
    private:
        time_t start_time;                          //起始时间
        time_t end_time;                            //结束时间
        bool state_flag;                            //定时器状态  有效true 无效false(可能删除)
        void* data;                                 //回调函数所需要的数据
        void* (*call_back)(void*);                  //回调函数
    public:
        timer_one(int time_ms,void* data,void* (*call_back)(void*));     //初始化函数  参数为 定时时长+回调函数
        void set_state_flag(bool flag);             //设置定时器状态
        void* run_call_back();                      //执行回调函数 
        bool operator >(timer_one&);                //大于号重载
	    bool operator <(timer_one&);
};

//定时器组  外部调用
class timers
{
    private:
        std::priority_queue <timer_one,std::vector<timer_one>,std::less<timer_one> > group_timers;     //优先队列
    public:
        timers();                                   
        timer_one* add_timer_one(timer_one timer);                                      //添加定时器
        timer_one* add_timers(int time_ms,void* data,void* (*call_back)(void*));        //添加定时器                                 //添加定时器
        bool delete_timers();                                                           //删除定时器      
        bool update_timers();                                                           //更新定时器
};





#endif