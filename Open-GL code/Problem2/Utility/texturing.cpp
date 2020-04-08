#include "texturing.hpp"
#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

//used to read image data
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint texture(const char* imgpath)
{

    GLuint tex;
    glGenTextures(1, &tex);

    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int pwidth, pheight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(imgpath, &pwidth, &pheight, &nrChannels,0);

    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pwidth, pheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else std:: cout<<"image failed"<<std::endl;

    stbi_image_free(data);
    
    return tex;
}
