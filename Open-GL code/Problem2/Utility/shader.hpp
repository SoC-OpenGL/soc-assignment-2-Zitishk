  
#ifndef shader_hpp
#define shader_hpp

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>



#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

struct ShaderProgram
{
    
    int vertexShader;
    
    GLint success;
    GLchar infoLog[512];
    
    int FragmentShader;
    
    int program;
    
    const char* vShaderCode;
    
    const char * fShaderCode;
    
    ShaderProgram(const char* vspath,const char* fspath);
    
    void Use(void);
    
    void setint(const std::string &name, int value);
    void setmat4(const std::string &name, glm::mat4 value );
    void setfloat(const std::string &name, float value);
    
};


#endif /* shader_hpp */

