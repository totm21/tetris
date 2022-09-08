
#include"timer.h"

timer::timer(int time_ms,void* data,void* (*call_back)(void*))
{
    this->start_time=clock();
    this->end_time=this->start_time+time_ms;
    this->data=data;
    this->call_back=call_back;
}

void* timer::run_call_back()
{
    return this->call_back(this->data);
}