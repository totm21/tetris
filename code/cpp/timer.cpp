
#include"timer.h"

Time_program* time_program=new Time_program();
Timers* timers=new Timers();
Timing* timing=new Timing();

Time_program::Time_program()
{
    this->flag_state=false;
    this->now_time=0;
    this->last_time=this->get_system_time();
}

long long Time_program::get_system_time()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

long long Time_program::get_program_time()
{
    return this->now_time;
}

void Time_program::update()
{
    long long time_system=this->get_system_time();
    if(time_system!=this->last_time)
    {
        if(this->flag_state)
        {
            ++this->now_time;
        }
        else
        {
            this->now_time+=time_system-this->last_time;
        }
        this->last_time=time_system;
    }
    return ;
}

void Time_program::set_flag_state(bool flag)
{
    this->flag_state=flag;
    return ;
}

bool Time_program::get_flag_state()
{
    return this->flag_state;
}

Timer_one::Timer_one(int time_ms,void* data,void* (*call_back)(void*))
{
    this->start_time=time_program->get_program_time();
    this->end_time=this->start_time+time_ms;
    this->state_flag=true;
    this->data=data;
    this->call_back=call_back;
}
Timer_one::~Timer_one()
{
    
}

long long Timer_one::get_start_time()
{
    return this->start_time;
}

long long Timer_one::get_end_time()
{
    return this->end_time;
}

bool Timer_one::compare_time_t(long long time_)
{
    if(time_>=this->end_time)
    {
        return true;
    }
    return false;
}

void Timer_one::set_state_flag(bool flag)
{
    this->state_flag=flag;
    return ;
}

bool Timer_one::get_state_flag()
{
    return this->state_flag;
}

bool Timer_one::delete_timers()
{
    this->state_flag=false;
    return true;
}

void* Timer_one::run_call_back()
{
    if(this->state_flag)
        return this->call_back(this->data);
    else
        return nullptr;
}

bool Timer_one::operator >(Timer_one& T)
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

bool Timer_one::operator <(Timer_one& T)
{
    return !(*this>T);
}

bool TIME_ONE_COMPARE::operator ()(Timer_one *A,Timer_one *B)
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

Timers::Timers()
{

}

Timer_one* Timers::add_timer_one(Timer_one* timer)
{
    if(timer==nullptr)
        return nullptr;
    this->group_timers.push(timer);
    return timer;
}

Timer_one* Timers::add_timers(int time_ms,void* data,void* (*call_back)(void*))
{
    Timer_one *timer=new Timer_one(time_ms,data,call_back);
    return this->add_timer_one(timer);
}

bool Timers::delete_timers(Timer_one* timer)
{
    if(timer==nullptr)
        return false;
    timer->set_state_flag(false);
    return true;
}

bool Timers::update_timers()
{
    time_program->update();
    long long now_time = time_program->get_program_time();
    while(!this->group_timers.empty())
    {
        Timer_one* top_timer=this->group_timers.top();
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

Timing::Timing()
{
    this->start_time=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
} 

Timing::~Timing()
{

}

long long Timing::get_duration()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()-this->start_time;
}

void Timing::restart()
{
    this->start_time=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
} 

