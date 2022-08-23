
#ifndef WIN_ME
#define WIN_ME

/*
    �����ڻ���
    @auther:    ����
    @date:      2022.8.21
*/

#include<iostream>
#include<windows.h>
#include<string>

#include"../resources/resources.h"

class Win
{
    private:
        WNDCLASS wndclass;
        HWND hwnd;
        MSG msg;
    public:
        Win();
        Win(HINSTANCE hInstance);
        //ע�ᴰ����
        void register_class(); 
        //��������
        void create_window(LPCTSTR name,int location_x,int location_y,int width,int high);    
        //��ʾ����
        void show_window();      
        //���´���
        void updata_window();     
        //��Ϣѭ��
        void loop_message();
        //��������̨����
        void create_console();


        //��
        void start_win(LPCTSTR name,int location_x,int location_y,int width,int high);
};

//������Ĭ�ϴ��ڴ�����
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



#endif