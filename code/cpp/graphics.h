
#ifndef __GRAPHICS__ME__
#define __GRAPHICS__ME__

/*
    图形绘制 引入openGL
    @auther:    程智
    @date:      2022.9.25
*/

#define GLFW_EXPOSE_NATIVE_WIN32
#include<windows.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<GLFW/glfw3native.h>
#include<imm.h>
#include<tchar.h>

#include"log.h"

#include"../../resources/resources.h"

#include"expands/stb_image.h"

#pragma comment (lib ,"imm32.lib")

class Dot2
{
    private:
        int x;
        int y;
    public:
        Dot2();
        Dot2(int x,int y);
        ~Dot2();
        void set_dot(int x,int y);
        void set_dot_x(int x){this->x=x;return;};
        void set_dot_y(int y){this->y=y;return;};
        int get_x(){return this->x;};
        int get_y(){return this->y;};
        bool operator <(Dot2 &dot);                 //小于号重载  基于x
        bool operator >(Dot2 &dot);                 //大于号重载  基于x
        bool operator ==(Dot2 &dot);
};

class Graphics
{
    private:
        GLFWwindow* window;
        HBITMAP map;
        HDC mem_hdc;         //内存dc

        HWND hwnd;
        HDC hdc;        //dc
        HPEN pen;       //画笔
        HBRUSH hbrush;  //画刷
    public:
        Graphics();
        ~Graphics();
        void init(const char* name,int define_IMG,int width,int high);         //初始化
        void set_title_ico(int define_IMG);                                    //设置图标
        bool update();                                                         //推进一次系统
        void kill_me();                                                        //释放资源

};

void framebuffer_size_callback(GLFWwindow* window, int width, int high);
void processInput(GLFWwindow *window);

extern Graphics* graphics;

#endif
