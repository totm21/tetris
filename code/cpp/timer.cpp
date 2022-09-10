
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

bool CMP_TIMER::operator()(timer_one* A,timer_one* B)
{
    if(A->end_time>B->end_time)
    {
        return true;
    }
    else if(A->end_time==B->end_time)
    {
        if(A->start_time<=B->start_time)
        {
            return true;
        }
    }
    return false;
}

timers::timers()
{

}

timer_one* timers::add_timer_one(timer_one* timer)
{
    this->group_timers.push(timer);
    return timer;
}

timer_one* timers::add_timers(int time_ms,void* data,void* (*call_back)(void*))
{
    timer_one *timer=new timer_one(time_ms,data,call_back);
    return this->add_timer_one(timer);
}

bool timers::delete_timers(timer_one* timer)
{
    timer->set_state_flag(false);
    return true;
}

