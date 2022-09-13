

#ifndef _TIMER_ME_
#define _TIMER_ME_

/*
    定时器实现--采用优先队列实现  
    本定时器采用单例模式
    还有另外一种时间轮定时器,但这个更适用于数据量大的情况,暂时优先队列就满足使用,所以暂时先不添加
    后续考虑时间轮+优先队列 实现大数据量
    @auther:    程智
    @date:      2022.9.13
    @alter:     2022.9.13
*/

#include<iostream>
#include<vector>
#include<queue>
#include<chrono>
#include<ctime>

//单个定时器定义
class timer_one
{
    private:
        long long start_time;                       //起始时间
        long long end_time;                         //结束时间
        bool state_flag;                            //定时器状态  有效true 无效false(可能删除)
        void* data;                                 //回调函数所需要的数据
        void* (*call_back)(void*);                  //回调函数
    public:
        timer_one(int time_ms,void* data,void* (*call_back)(void*));     //初始化函数  参数为 定时时长+回调函数
        long long get_start_time();
        long long get_end_time();
        bool compare_time_t(long long time_);       //时间比较
        void set_state_flag(bool flag);             //设置定时器状态
        bool get_state_flag();                      //获得定时器状态
        bool delete_timers();                       //伪删除                        
        void* run_call_back();                      //执行回调函数 
        bool operator >(timer_one&);                //大于号重载
	    bool operator <(timer_one&);  
};

//此处是定义排序  尝试重定义自己的() 但显示优先队列没有默认构造函数 暂时无法解决 丑陋也就先丑陋着吧
class TIME_ONE_COMPARE
{
    public:
        bool operator ()(timer_one*,timer_one*);  
};

//定时器组  外部调用
class timers
{
    private:
        std::priority_queue <timer_one*,std::vector<timer_one*>,TIME_ONE_COMPARE> group_timers;     //优先队列
    public:
        timers();                                   
        timer_one* add_timer_one(timer_one *timer);                                     //添加定时器
        timer_one* add_timers(int time_ms,void* data,void* (*call_back)(void*));        //添加定时器                          
        bool delete_timers(timer_one* timer);                                           //删除定时器      
        bool update_timers();                                                           //更新定时器
};




#endif