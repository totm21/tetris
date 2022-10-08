
#include"graphics.h"

Graphics* graphics=new Graphics();

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

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

void Graphics::init(const char* name,int define_IMG,int width,int high)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	this->window = glfwCreateWindow(width, high, name, NULL, NULL);
    
    this->hwnd = glfwGetWin32Window(this->window);
    this->set_title_ico(define_IMG);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glViewport(0, 0, width, high);

    //英文输入法切换 ENG
    this->set_keyboard_input_method(english);

    return ;
}

void Graphics::set_title_ico(int define_IMG)
{
    HICON hIcon = ::LoadIcon((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(define_IMG));
    ::SendMessage(this->hwnd,WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    ::SendMessage(this->hwnd,WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    return ;
}

void Graphics::set_keyboard_input_method(Language language)
{
    HKL hkl;
    switch(language)
    {
        case english:
            hkl = LoadKeyboardLayout(_T("00000409"), KLF_ACTIVATE);
            break;
        case chinese:
            hkl = LoadKeyboardLayout(_T("00000804"), KLF_ACTIVATE);
            break;
            
    }
    PostMessage(this->hwnd, WM_INPUTLANGCHANGEREQUEST, (WPARAM)TRUE, (LPARAM)hkl);
}

bool Graphics::update()
{
    if(!glfwWindowShouldClose(window))
    {
        glfwSetKeyCallback(window, key_callback);
        //processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
        return true;
    }
    return false;
}

void Graphics::kill_me()
{
    glfwTerminate();
    return;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        logs->WRITE_LOG(Info,"A is pressed");
    }
    return ;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int high)
{
    glViewport(0, 0, width, high);
}


bool flag[2]={0};

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
        
   if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)       //按下
	{
        if(!flag[0])
        {
	        logs->WRITE_LOG(Info,"A is pressed");
            flag[0]=true;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)      //抬起
    {
        flag[0]=false;
    }

	// 接受键盘 B 键，随机修改背景颜色
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)       //按下
	{
        if(!flag[1])
        {
	        logs->WRITE_LOG(Info,"B is pressed");
            flag[1]=true;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE)      //抬起
    {
        flag[1]=false;
    }
    return ;
}

