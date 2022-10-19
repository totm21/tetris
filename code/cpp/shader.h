
#ifndef _SHADER_ME_
#define _SHADER_ME_

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include<vector>

#include"expands/stb_image.h"

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
        unsigned char *data;        //图片数据
        bool is_use;                //是否使用                 
        Textures_explain();
        //初始化
        void init();                
        //设置策略
        void set_strategy(unsigned int base_strategy,unsigned int max_strategy,unsigned int min_strategy);          
        //加载并绑定纹理-图片
        bool load_image(std::string file);  
        //绑定并加载纹理
        bool creat_testres(std::string file,unsigned int base_strategy,unsigned int max_strategy,unsigned int min_strategy);
        //绑定纹理单元
        void bind_texture(int index);
        //设置是否启用
        void set_use(bool is_use);
};


class Shader
{
    private:
    public:
        //程序ID
        unsigned int ID;
        unsigned int VAO,VBO,EBO;
        Textures_explain* testures;          //纹理组 openGL最大支持16个 0-15
        char number_testures;                //纹理数量
    public:
        // 构造器读取并构建着色器
        Shader(const char* vertexPath,const char* fragmentPath);
        //设置并解析顶点
        bool set_vertices(float* vertices,int vertices_size,unsigned int* indices,int indices_size,Vertices_explain vertices_explain);
        //初始化纹理(仅分配空间)
        bool creat_textures(int number);
        //重新初始化纹理(仅分配空间)
        bool recreat_textures(int number);
        //释放纹理
        bool delete_textures();
        //设置index号纹理
        bool set_textures(int index,std::string file,unsigned int base_strategy,unsigned int max_strategy,unsigned int min_strategy);
        //统一绑定纹理
        void bind_textures();
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