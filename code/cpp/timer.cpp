
#include"timer.h"

timer_one::timer_one(int time_ms,void* data,void* (*call_back)(void*))
{
    this->start_time=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    this->end_time=this->start_time+time_ms;
    this->state_flag=true;
    this->data=data;
    this->call_back=call_back;
}

long long timer_one::get_start_time()
{
    return this->start_time;
}

long long timer_one::get_end_time()
{
    return this->end_time;
}

bool timer_one::compare_time_t(long long time_)
{
    if(time_>=this->end_time)
    {
        return true;
    }
    return false;
}

void timer_one::set_state_flag(bool flag)
{
    this->state_flag=flag;
    return ;
}

bool timer_one::get_state_flag()
{
    return this->state_flag;
}

bool timer_one::delete_timers()
{
    this->state_flag=false;
    return true;
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

bool TIME_ONE_COMPARE::operator ()(timer_one *A,timer_one *B)
{
    if(A->get_end_time()>B->get_end_time())
    {
        return true;
    }
    else if(A->get_end_time()==B->get_end_time())
    {
        if(A->get_start_time()<=B->get_start_time())
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
    if(timer==nullptr)
        return nullptr;
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
    if(timer==nullptr)
        return false;
    timer->set_state_flag(false);
    return true;
}

bool timers::update_timers()
{
    long long now_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    while(!this->group_timers.empty())
    {
        timer_one* top_timer=this->group_timers.top();
        if(top_timer->compare_time_t(now_time))
        {
            if(top_timer->get_state_flag())
            { 
                top_timer->run_call_back();
            }
            this->group_timers.pop();
            delete top_timer;
            top_timer=nullptr;
        }
        else
        {
            break;
        }
    }
    return true;
}
