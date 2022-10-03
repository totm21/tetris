

#ifndef _TIMER_ME_
#define _TIMER_ME_

/*
    定时器实现--采用优先队列实现  
    本定时器采用单例模式
    还有另外一种时间轮定时器,但这个更适用于数据量大的情况,暂时优先队列就满足使用,所以暂时先不添加
    后续考虑时间轮+优先队列 实现大数据量
    以及时间相关class和函数

    存在误差-----不能每一毫秒都抓到 同时与系统时间分离支持暂停

    @auther:    程智
    @date:      2022.9.13
    @alter:     2022.10.3
*/

#include<iostream>
#include<vector>
#include<queue>
#include<chrono>
#include<ctime>
#include"log.h"

class Time_program
{
    private:
        long long now_time;
        long long last_time;
        bool flag_state;            //状态标记位   false为无暂停  true为暂停
    public:
        Time_program();
        long long get_system_time();
        long long get_program_time();
        void update();
        void set_flag_state(bool flag);
        bool get_flag_state();
};

//单个定时器定义
class Timer_one
{
    private:
        long long start_time;                       //起始时间
        long long end_time;                         //结束时间
        bool state_flag;                            //定时器状态  有效true 无效false(可能删除)
        void* data;                                 //回调函数所需要的数据  注意该数据由调用者在回调中释放!!!
        void* (*call_back)(void*);                  //回调函数
    public:
        Timer_one(int time_ms,void* data,void* (*call_back)(void*));     //初始化函数  参数为 定时时长+回调函数
        ~Timer_one();
        long long get_start_time();
        long long get_end_time();
        bool compare_time_t(long long time_);       //时间比较
        void set_state_flag(bool flag);             //设置定时器状态
        bool get_state_flag();                      //获得定时器状态
        bool delete_timers();                       //伪删除                        
        void* run_call_back();                      //执行回调函数 
        bool operator >(Timer_one&);                //大于号重载
	    bool operator <(Timer_one&);  
};

//此处是定义排序  尝试重定义自己的() 但显示优先队列没有默认构造函数 暂时无法解决 丑陋也就先丑陋着吧
class TIME_ONE_COMPARE
{
    public:
        bool operator ()(Timer_one*,Timer_one*);  
};

//定时器组  外部调用
class Timers
{
    private:
        std::priority_queue <Timer_one*,std::vector<Timer_one*>,TIME_ONE_COMPARE> group_timers;     //优先队列
    public:
        Timers();                                   
        Timer_one* add_timer_one(Timer_one *timer);                                     //添加定时器
        Timer_one* add_timers(int time_ms,void* data,void* (*call_back)(void*));        //添加定时器                          
        bool delete_timers(Timer_one* timer);                                           //删除定时器      
        bool update_timers();                                                           //更新定时器
};

//计时器组
class Timing
{
    private:
        long long start_time;                       //起始时间
    public:
        Timing();   
        ~Timing();   
        long long get_duration();                   //获得从开始到现在的时长
        void restart();                             //重新开始记录

};

extern Time_program* time_program;
extern Timers* timers;
extern Timing* timing;

#endif