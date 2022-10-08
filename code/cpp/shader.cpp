
#include"shader.h"

Shader::Shader(const char* vertex_code,const char* fragment_code)
{

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // 顶点着色器
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_code, NULL);
    glCompileShader(vertex);
    // 打印编译错误
    this->check_compile_code(vertex);

    // 片段着色器
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_code, NULL);
    glCompileShader(fragment);
    this->check_compile_code(fragment);

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertex);
    glAttachShader(this->ID, fragment);
    glLinkProgram(this->ID);
    // 打印连接错误
    glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
        logs->WRITE_LOG(Error,infoLog);
    }

    // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

bool Shader::set_vertices(float* vertices,int vertices_size,unsigned int* indices,int indices_size,Vertices_explain vertices_explain)
{
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
    glBindVertexArray(this->VAO);
    //顶点数组复制
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

    //告诉openGL 如何处理数据
    for(int i=0;i<vertices_explain.group_number;i++)
    {
        glVertexAttribPointer(vertices_explain.groups[i].a, vertices_explain.groups[i].b, vertices_explain.type_opengl, GL_FALSE, vertices_explain.data_len*vertices_explain.type_size, (void*)((long long)(vertices_explain.groups[i].c*vertices_explain.type_size)));
        glEnableVertexAttribArray(vertices_explain.groups[i].a);
    }
    
    return true;
}

bool Shader::check_compile_code(unsigned int shader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        logs->WRITE_LOG(Error,infoLog);
        return false;
    };
    return true;
}

void Shader::use()
{
    glUseProgram(this->ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
} 

