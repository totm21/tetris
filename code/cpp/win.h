
#ifndef _WIN_ME_
#define _WIN_ME_

/*
    主窗口绘制
    @auther:    程智
    @date:      2022.8.21
*/

#include<iostream>
#include<windows.h>
#include<string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<GLFW/glfw3native.h>

#include"../../resources/resources.h"

class Win
{
    private:
        WNDCLASS wndclass;
        HWND hwnd;
        MSG msg;
    public:
        Win();
        Win(HINSTANCE hInstance);
        ~Win();
        //设置句柄
        void set_hInstance(HINSTANCE hInstance,int define_img);
        //注册窗口类
        void register_class(); 
        //创建窗口
        void create_window(LPCTSTR name,int location_x,int location_y,int width,int high);    
        //显示窗口
        void show_window();      
        //更新窗口
        void update_window();     
        //消息循环
        bool loop_message();
        //创建控制台窗口
        void create_console();
       
        //总
        void start_win(LPCTSTR name,int location_x,int location_y,int width,int high);

        HWND get_hwnd();
};

//程序内默认窗口处理函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//按键处理函数
void handle_key(WPARAM wParam,LPARAM lParam);

extern Win* win;

#endif