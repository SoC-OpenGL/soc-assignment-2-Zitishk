
#ifndef cube_hpp
#define cube_hpp

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

struct cube
{
    GLuint VBO;
    GLuint EBO;
    GLuint VAO;
    cube(void);
    cube(float a,int b);
    
};

#endif /* cube_hpp */
