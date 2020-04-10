#include "shader.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>


#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

ShaderProgram :: ShaderProgram(const char* vspath,const char* fspath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vspath);
        fShaderFile.open(fspath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    vShaderCode = vertexCode.c_str();
    fShaderCode = fragmentCode.c_str();
    
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vertexShader, 1,&vShaderCode,NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS,&success);
    
    if(!success)
    {
        glGetShaderInfoLog(vertexShader,512, NULL,infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(FragmentShader,1,&fShaderCode, NULL);
    glCompileShader(FragmentShader);
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS,&success);
    
    if(!success)
    {
        glGetShaderInfoLog(FragmentShader,512, NULL,infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    
    program=glCreateProgram();
    glAttachShader(program,vertexShader);
    glAttachShader(program,FragmentShader);
    glLinkProgram(program);
    //check
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(program, 512,NULL, infoLog);
        std::cout<<"ERROR in program::Linking failed\n"<< infoLog<< std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(FragmentShader);
    
}

void ShaderProgram::Use()
{
    glUseProgram(program);
}

void ShaderProgram::setint(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(program,name.c_str()),value);
}

void ShaderProgram::setfloat(const std::string &name, float value)
{
    glUniform1f(glGetUniformLocation(program,name.c_str()),value);
}

void ShaderProgram::setmat4(const std::string &name, glm::mat4 value)
{
    int Loc = glGetUniformLocation(program, name.c_str());
    glUniformMatrix4fv(Loc, 1, GL_FALSE, glm::value_ptr(value));
}

