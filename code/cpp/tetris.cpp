

//此处为官方头文件

#include<iostream>
#include<windows.h>
#include<fstream>
#include<string>
#include<iterator>
#include<math.h>

//此处为扩展头文件
#include"expands/lua/lua.hpp"
#include"expands/json/json.h"
#include"expands/stb_image.h"

//此处为自定义头文件
#include"register.h"
#include"timer.h"
#include"log.h"
#include"graphics.h"
#include"shader.h"

HINSTANCE hInstance;

/*
测试代码----暂时留存----抄来的
void readFileJson()
{
	Json::Reader reader;
	Json::Value root;
 
	//从文件中读取，保证当前文件有demo.json文件  
	std::ifstream in("configure/demo.json", std::ios::binary);
 
	if (!in.is_open())
	{
		std::cout << "Error opening file\n";
		return;
	}
 
	if (reader.parse(in, root))
	{
		//读取根节点信息  
		std::string name = root["name"].asString();
		int age = root["age"].asInt();
		std::string sex = root["sex"].asString();
 
		std::cout << "My name is " << name << std::endl;
		std::cout << "I'm " << age << " years old" << std::endl;
		std::cout << "I'm a " << sex << std::endl;
 
		//读取子节点信息  
		std::string friend_name = root["friends"]["friend_name"].asString();
		int friend_age = root["friends"]["friend_age"].asInt();
		std::string friend_sex = root["friends"]["friend_sex"].asString();
 
		std::cout << "My friend's name is " << friend_name << std::endl;
		std::cout << "My friend's sex is "<<friend_sex << std::endl;
		std::cout << "My friend is " << friend_age << " years old" << std::endl;
 
		//读取数组信息  
		std::cout << "Here's my hobby:" << std::endl;
		for (unsigned int i = 0; i < root["hobby"].size(); i++)
		{
			std::string ach = root["hobby"][i].asString();
			std::cout << ach << '\t';
		}
		std::cout << std::endl;
 
		std::cout << "Reading Complete!" << std::endl;
	}
	else
	{
		std::cout << "parse error\n" << std::endl;
	}
 
	in.close();
}
*/
//int a[3]={10,2000,100};
void* call_back(void* T)
{
	int *t=(int*)T;
	std::cout<<*t<<" "<<time_program->get_program_time()<<std::endl;
	
	//Timer_one* tim1=new Timer_one(100,(void*)(a),call_back);
	//timers->add_timer_one(tim1);
	return nullptr;
}


//片段着色器源码
const char *fragmentShaderSource=
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n" 
"in vec2 TexCoord;\n"
"uniform sampler2D texture1;\n"
"uniform sampler2D texture2;\n"
"void main()\n"
"{\n"
"	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);"
"}\n\0";




//GLSL语言 着色源码 嵌入字符串
const char *vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"	TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
"}\0";

float vertices[] =
{
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	/*
	// 位置              // 颜色			//纹理
	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,	1.0f, 0.0f, // 右下角
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,	0.0f, 0.0f, // 左下角
	0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.5f, 1.0f // 上中
	*/
};

unsigned int indices[] =
{
        // 注意索引从0开始! 
        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
        // 这样可以由下标代表顶点组合成矩形
        //0, 1, 2, // 第一个三角形
		0, 1, 3,
		1, 2, 3
};

int main()
{	
	//hInstance = GetModuleHandle(nullptr);
	
	AllocConsole();
	
#ifdef _WIN32
	system("chcp 65001");	//utf-8乱码问题
#endif
    freopen("CONOUT$", "w", stdout);

	lua_State *lua = luaL_newstate(); 
    if(lua == nullptr)
    {
        return 0;
    }

    luaL_requiref(lua, "CFuncName", luaopen_C_Func_Name, 1);/*将C语言函数库注册到Lua环境中*/

	luaL_openlibs(lua);
    luaL_dofile(lua, "../code/lua/debugPrint.lua");
	lua_close(lua);


	logs->WRITE_LOG(Logs,"这是一个测试 希望你能看到");
	
	graphics->init("俄罗斯方块",IMG_ICON_HUANXIONG,1000,600);

	logs->WRITE_LOG(Logs,"开始测试");

	logs->WRITE_LOG(Logs,"测试结束,时长为 : "+std::to_string(timing->get_duration()));
	
	//画线
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//充满
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Shader shader(vertexShaderSource,fragmentShaderSource);
	Vertices_explain ver;
	ver.type_size = sizeof(float);
	ver.type_opengl = GL_FLOAT;
	ver.group_number = 3;
	ver.data_len = 8;
	Group3<int,int,int> group3[3];
	group3[0].a=0;
	group3[0].b=3;
	group3[0].c=0;
	group3[1].a=1;
	group3[1].b=3;
	group3[1].c=3;
	group3[2].a=2;
	group3[2].b=2;
	group3[2].c=6;
	ver.groups.push_back(group3[0]);
	ver.groups.push_back(group3[1]);
	ver.groups.push_back(group3[2]);

	shader.set_vertices(vertices,sizeof(vertices),indices,sizeof(indices),ver);
	
	unsigned int texture1,texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load("../resources/image/root.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
	
	glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("../resources/image/2.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
	
	shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

	while(graphics->update())
	{
		timers->update();
		//清空
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		/*
		随时间变色
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(graphics->shaderProgram, "ourColor");
		glUseProgram(graphics->shaderProgram);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		*/
		
		glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
		shader.use();
		//激活程序对象
    	glBindVertexArray(shader.get_VAO());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    	//glDrawArrays(GL_TRIANGLES, 0, 3);
	}

 	FreeConsole();
    return 0;
}