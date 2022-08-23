#include<iostream>
#include<windows.h>

#include"win.h"

HINSTANCE hInstance;



int main()
{
    //hInstance = GetModuleHandle(TEXT("tetris.exe"));
    

    
    Win win(hInstance);
    win.start_win(TEXT("¶íÂÞË¹·½¿é"),200,100,1000,600);
    
    
    return 0;
}