#include<iostream>
#include<windows.h>

#include"win.h"

HINSTANCE hInstance;



int main()
{
    hInstance = GetModuleHandle(TEXT("tetris.exe"));
    AllocConsole();
    freopen("CONOUT$", "w", stdout);


    Win win(hInstance);
    win.start_win("¶íÂÞË¹·½¿é",100,100,300,500);
    
    return 0;
}