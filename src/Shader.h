#ifndef SHADERS_H
#define SHADERS_H

#include "glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    GLint ProgramID;
    
    Shader(const std::string VertexPath, const std::string FragmentPath);
    
    void use();
    void setBool(const std::string &name, GLboolean value) const;
    void setInt(const std::string &name, GLint value) const;
    void setFloat(const std::string &name, GLfloat value) const;

    void destroy();

    ~Shader();
};

Shader::Shader(const std::string VertexPath, const std::string FragmentPath)
{
    std::ifstream VertexShader_File;   
    std::ifstream FragmentShader_File;   

    std::string VertexShader_Source;
    std::string FragmentShader_Source;

    try
    {
        VertexShader_File.open(VertexPath);
        FragmentShader_File.open(FragmentPath);

        std::stringstream VertexStream, FragmentStream;

        VertexStream << VertexShader_File.rdbuf();
        FragmentStream << FragmentShader_File.rdbuf();

        VertexShader_File.close();
        FragmentShader_File.close();

        VertexShader_Source = VertexStream.str();
        FragmentShader_Source = FragmentStream.str();

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    const char* VertexSource = VertexShader_Source.c_str();
    const char* FragmentSource = FragmentShader_Source.c_str();

    int success;
    char infoLog[512];

    /* Cria e compila os shaders */
    GLuint Vertex, Fragment;

    std::cout << "Compiling Vertex shaders at " + VertexPath << "\n";

    Vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(Vertex, 1, &VertexSource, NULL);
    glCompileShader(Vertex);

    glGetShaderiv(Vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(Vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    std::cout << "Compiling Fragment shaders at " + FragmentPath << "\n";

    Fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(Fragment, 1, &FragmentSource, NULL);
    glCompileShader(Fragment);

    glGetShaderiv(Fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(Fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    ProgramID = glCreateProgram();
    glAttachShader(ProgramID, Vertex);
    glAttachShader(ProgramID, Fragment);
    glLinkProgram(ProgramID);

    glGetProgramiv(ProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(Vertex);
    glDeleteShader(Fragment);
    
}

void Shader::use()
{
    glUseProgram(ProgramID);
}

void Shader::setBool(const std::string& name, GLboolean value) const
{
    GLint location = glGetUniformLocation(ProgramID, name.c_str());
    glUniform1i(location, (GLint) value);
}

void Shader::setFloat(const std::string& name, GLfloat value) const
{
    GLint location = glGetUniformLocation(ProgramID, name.c_str());
    glUniform1f(location, value);
}

void Shader::setInt(const std::string& name, GLint value) const
{
    GLint location = glGetUniformLocation(ProgramID, name.c_str());
    glUniform1i(location, value);
}

void Shader::destroy()
{
    glDeleteShader(ProgramID);
}

Shader::~Shader()
{
}


#endif
