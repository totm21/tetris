
#ifndef _SHADER_ME_
#define _SHADER_ME_

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>

#include"log.h"
#include"template.h"

/*
    渲染封装
    @auther:    程智
    @date:      2022.10.8
*/

class Vertices_explain
{
    public:
        int type_size;      //单个数据长度
        int type_opengl;    //数据类型 例: 浮点型:GL_FLOAT
        int data_len;       //一组数据的个数
        int group_number;   //组数
        std::vector<Group3<int,int,int>> groups;        //对应每一组的数据 1.组号 2.单个点的数据个数 3.偏移量 
};

class Textures_explain
{
    public:
        unsigned int texture;
        char hierarchy;             //层级
        unsigned int base_strategy,max_strategy,min_strategy;          //基础策略  最大策略 最小策略
        
};




class Shader
{
    private:
        //程序ID
        unsigned int ID;
        unsigned int VAO,VBO,EBO;
        
    public:
        // 构造器读取并构建着色器
        Shader(const char* vertexPath,const char* fragmentPath);
        //设置并解析顶点
        bool set_vertices(float* vertices,int vertices_size,unsigned int* indices,int indices_size,Vertices_explain vertices_explain);
        //设置并解析纹理
        bool set_textures();
        // 编译错误检查
        bool check_compile_code(unsigned int shader); 
        // 使用/激活程序
        void use();
        // uniform工具函数
        void setBool(const std::string &name, bool value) const;  
        void setInt(const std::string &name, int value) const;   
        void setFloat(const std::string &name, float value) const;
        
        unsigned int get_ID(){return this->ID;};
        unsigned int get_VAO(){return this->VAO;};
        unsigned int get_VBO(){return this->VBO;};
        unsigned int get_EBO(){return this->EBO;};
};


#endif