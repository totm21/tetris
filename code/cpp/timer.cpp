
#include"timer.h"

timer_one::timer_one(int time_ms,void* data,void* (*call_back)(void*))
{
    this->start_time=clock();
    this->end_time=this->start_time+time_ms;
    this->state_flag=true;
    this->data=data;
    this->call_back=call_back;
}

void timer_one::set_state_flag(bool flag)
{
    this->state_flag=flag;
    return ;
}

void* timer_one::run_call_back()
{
    return this->call_back(this->data);
}