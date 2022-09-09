
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
    if(this->state_flag)
        return this->call_back(this->data);
    else
        return nullptr;
}

bool timer_one::operator >(timer_one& T)
{
    if(this->end_time>T.end_time)
    {
        return true;
    }
    else if(this->end_time==T.end_time)
    {
        if(this->start_time<=T.start_time)
        {
            return true;
        }
    }
    return false;
}

bool timer_one::operator <(timer_one& T)
{
    return !(*this>T);
}



timers::timers()
{

}

timer_one* timers::add_timer_one(timer_one timer)
{
    return nullptr;
}