#include "cube.hpp"
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

cube:: cube()
{
   float vertices[]={
        // vertices            //texture coords
        -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,      1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,      1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,      1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,     0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,      1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,      1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,      1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,     0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,      1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,      1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,      0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,      0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,      0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,      1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,      1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,      1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,      1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,     0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,      1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,      1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,      1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,     0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,     0.0f, 1.0f
    };
    
    glGenVertexArrays(1,&VAO);
    
    glGenBuffers(1,&VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    
    
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
}
cube:: cube(float a)
{
    float vertices[]={
        
        // vertices            //texture coords
        -a, -a, -a,     0.0f, 0.0f,
        a, -a, -a,      1.0f, 0.0f,
        a,  a, -a,      1.0f, 1.0f,
        a,  a, -a,      1.0f, 1.0f,
        -a,  a, -a,     0.0f, 1.0f,
        -a, -a, -a,     0.0f, 0.0f,
        
        -a, -a,  a,     0.0f, 0.0f,
        a, -a,  a,      1.0f, 0.0f,
        a,  a,  a,      1.0f, 1.0f,
        a,  a,  a,      1.0f, 1.0f,
        -a,  a,  a,     0.0f, 1.0f,
        -a, -a,  a,     0.0f, 0.0f,
        
        -a,  a,  a,     1.0f, 0.0f,
        -a,  a, -a,     1.0f, 1.0f,
        -a, -a, -a,     0.0f, 1.0f,
        -a, -a, -a,     0.0f, 1.0f,
        -a, -a,  a,     0.0f, 0.0f,
        -a,  a,  a,     1.0f, 0.0f,
        
        a,  a,  a,      1.0f, 0.0f,
        a,  a, -a,      1.0f, 1.0f,
        a, -a, -a,      0.0f, 1.0f,
        a, -a, -a,      0.0f, 1.0f,
        a, -a,  a,      0.0f, 0.0f,
        a,  a,  a,      1.0f, 0.0f,
        
        -a, -a, -a,     0.0f, 1.0f,
        a, -a, -a,      1.0f, 1.0f,
        a, -a,  a,      1.0f, 0.0f,
        a, -a,  a,      1.0f, 0.0f,
        -a, -a,  a,     0.0f, 0.0f,
        -a, -a, -a,     0.0f, 1.0f,
        
        -a,  a, -a,     0.0f, 1.0f,
        a,  a, -a,      1.0f, 1.0f,
        a,  a,  a,      1.0f, 0.0f,
        a,  a,  a,      1.0f, 0.0f,
        -a,  a,  a,     0.0f, 0.0f,
        -a,  a, -a,     0.0f, 1.0f
    };
    
    glGenVertexArrays(1,&VAO);
    
    glGenBuffers(1,&VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    
    
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
}

cube:: cube(float a,int b)
{
    float vertices[]={
        
        // vertices            //texture coords
        -a, -a, -a,
        a, -a, -a,
        a,  a, -a,
        a,  a, -a,
        -a,  a, -a,
        -a, -a, -a,
        
        -a, -a,  a,
        a, -a,  a,
        a,  a,  a,
        a,  a,  a,
        -a,  a,  a,
        -a, -a,  a,
        
        -a,  a,  a,
        -a,  a, -a,
        -a, -a, -a,
        -a, -a, -a,
        -a, -a,  a,
        -a,  a,  a,
        
        a,  a,  a,
        a,  a, -a,
        a, -a, -a,
        a, -a, -a,
        a, -a,  a,
        a,  a,  a,
        
        -a, -a, -a,
        a, -a, -a,
        a, -a,  a,
        a, -a,  a,
        -a, -a,  a,
        -a, -a, -a,
        
        -a,  a, -a,
        a,  a, -a,
        a,  a,  a,
        a,  a,  a,
        -a,  a,  a,
        -a,  a, -a
    };
    
    glGenVertexArrays(1,&VAO);
    
    glGenBuffers(1,&VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    
    
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
}

