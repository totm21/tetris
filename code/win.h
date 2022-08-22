
#ifndef WIN_ME
#define WIN_ME

/*
    主窗口绘制
    @auther:    程智
    @date:      2022.8.21
*/

#include<iostream>
#include<windows.h>
#include<string>


class Win
{
    private:
        WNDCLASS wndclass;
        HWND hwnd;
        MSG msg;
    public:
        Win();
        Win(HINSTANCE hInstance);
        //注册窗口类
        void register_class(); 
        //创建窗口
        void create_window(std::string name,int location_x,int location_y,int width,int high);    
        //显示窗口
        void show_window();      
        //更新窗口
        void updata_window();     
        //消息循环
        void loop_message();

        //总
        void start_win(std::string name,int location_x,int location_y,int width,int high);
};

//string 转 LPCWSTR
LPCWSTR stringToLPCWSTR(std::string orig);

//程序内默认窗口处理函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



#endif