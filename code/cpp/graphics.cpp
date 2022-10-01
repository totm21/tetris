
#include"graphics.h"

Graphics* graphics=new Graphics();

Dot2::Dot2()
{

}

Dot2::Dot2(int x,int y)
{
    this->x=x;
    this->y=y;
}

Dot2::~Dot2()
{

}

void Dot2::set_dot(int x,int y)
{
    this->x=x;
    this->y=y;
    return ;
}

bool Dot2::operator <(Dot2 &dot)
{
    if(this->get_x()<dot.get_x())
    {
        return true;
    }
    else if(this->get_x()==dot.get_x())
    {
        if(this->get_y()<dot.get_y())
        {
            return true;
        }
    }
    return false;
}

bool Dot2::operator >(Dot2 &dot)
{
    if(this->get_x()>dot.get_x())
    {
        return true;
    }
    else if(this->get_x()==dot.get_x())
    {
        if(this->get_y()>dot.get_y())
        {
            return true;
        }
    }
    return false;
}

bool Dot2::operator ==(Dot2 &dot)
{
    if(this->get_x()==dot.get_x()&&this->get_y()==this->get_y())
    {
        return true;
    }
    return false;
}

Graphics::Graphics()
{
    
}

Graphics::~Graphics()
{
    ReleaseDC(hwnd,hdc);
}

void Graphics::init(const char* name,int width,int height)
{
    logs->LOG_WRITE(Logs,name);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //创建glfw窗口
	this->window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return ;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return ;
    }    

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return ;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Graphics::draw_pixel(int x,int y,COLORREF color)
{
    SetPixel(this->hdc,x,y,color);
	return ;
}

void Graphics::draw_pixel(Dot2 dot,COLORREF color)
{
    this->draw_pixel(dot.get_x(),dot.get_y(),color);
    return ;
}


void Graphics::draw_line(int x1,int y1,int x2,int y2,bool check,COLORREF color)
{
    if(check)
    {
        if(x1>x2)
        {
            int temp=x1;
            x1=x2;
            x2=temp;
            temp=y1;
            y1=y2;
            y2=temp;
        }
    }
    std::cout<<x1<<' '<<x2<<std::endl;
    double k=((double)y2-y1)/((double)x2-x1);
    double base=y1-k*x1;
    for(int i=x1;i<=x2;i++)
    {
        this->draw_pixel(i,(k*i+base)+0.5,color);
    }
    return ;
}

void Graphics::draw_line(Dot2 dot1,Dot2 dot2,bool check,COLORREF color)
{
    this->draw_line(dot1.get_x(),dot1.get_y(),dot2.get_x(),dot2.get_y(),check,color);
    return ;
}

//大体实现为连接三条线
void Graphics::draw_triangle(int x1,int y1,int x2,int y2,int x3,int y3,bool check,COLORREF color)
{
    return;
}



/*

    此处留档 不删  CPU绘图(大概率用不上)


COLORREF *arr = (COLORREF*) calloc(1920*1080, sizeof(COLORREF));

    // Temp HDC to copy picture
HBITMAP map = CreateBitmap(1920, // width. 512 in my case
                            1080, // height
                            1, // Color Planes, unfortanutelly don't know what is it actually. Let it be 1
                            8*4, // Size of memory for one pixel in bits (in win32 4 bytes = 4*8 bits)
                            (void*) arr); // pointer to array
    // Creating temp bitmap

//从内存中渲染画面-- 0-1 ms  后面再改
void Graphics::test()
{
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<100;j++)
        {
            arr[i*1920+j]=RGB(0,255,0);
        }
    }
    //刷新————存档
    SetBitmapBits(map,1920*1080,arr);
    
    
    HDC src = CreateCompatibleDC(this->hdc); // hdc - Device context for window, I've got earlier with GetDC(hWnd) or GetDC(NULL);
    SelectObject(src, map); // Inserting picture into our temp HDC
    // Copy image from temp HDC to window
    BitBlt(hdc, // Destination
        0,  // x and
        0,  // y - upper-left corner of place, where we'd like to copy
        1920, // width of the region
        1080, // height
        src, // source
        0,   // x and
        0,   // y of upper left corner  of part of the source, from where we'd like to copy
        SRCCOPY); // Defined DWORD to juct copy pixels. Watch more on msdn;

    DeleteDC(src); // Deleting temp HDC
    return ;
}

*/



