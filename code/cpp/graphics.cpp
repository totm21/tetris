
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
        logs->LOG_WRITE(Info,"A is pressed");
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
	        logs->LOG_WRITE(Info,"A is pressed");
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
	        logs->LOG_WRITE(Info,"B is pressed");
            flag[1]=true;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE)      //抬起
    {
        flag[1]=false;
    }
    return ;
}
//片段着色器源码
const char *fragmentShaderSource="#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0"; 

//GLSL语言 着色源码 嵌入字符串
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

void Graphics::test()
{
    //顶点
    //生成着色器对象
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //着色源码嵌入
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //源码编译
    glCompileShader(vertexShader);
    //编译结果检测
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    //若错误 则输出错误信息
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //源码绑定
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    //片段着色器编译
    glCompileShader(fragmentShader);

    //生成着色器程序
    shaderProgram = glCreateProgram();

    //着色器附加
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //链接检测
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }
    
    //对象删除
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //顶点
    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };
     
    glGenVertexArrays(1, &VAO);
    //生成缓冲对象
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
   
    //顶点数组复制
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //告诉openGL 如何处理数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    return ;
}

