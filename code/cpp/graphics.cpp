
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

void Graphics::init(const char* name,int define_IMG,int width,int height)
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
    
    this->hwnd = glfwGetWin32Window(this->window);
    HICON hIcon = ::LoadIcon((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(define_IMG));
    ::SendMessage(this->hwnd,WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    ::SendMessage(this->hwnd,WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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


