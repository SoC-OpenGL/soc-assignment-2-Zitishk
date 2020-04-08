
#include "skybox.hpp"
#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

//used to read image data
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint skox(void)
{
    
    GLuint texu;
    glGenTextures(1, &texu);
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, texu);
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    std::string faces[]={
        "/Users/Zitishk/Desktop/Problem2/Problem2/tex.jpg",
        "/Users/Zitishk/Desktop/Problem2/Problem2/tex.jpg",
        "/Users/Zitishk/Desktop/Problem2/Problem2/tex.jpg",
        "/Users/Zitishk/Desktop/Problem2/Problem2/tex.jpg",
        "/Users/Zitishk/Desktop/Problem2/Problem2/tex.jpg",
        "/Users/Zitishk/Desktop/Problem2/Problem2/tex.jpg"
     };
    

    for(int i=0;i<6;i++)
    {
        int pwidth, pheight, nrChannels;
        //stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(faces[i].c_str(), &pwidth, &pheight, &nrChannels,0);
        
        if(data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, pwidth, pheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else std:: cout<<"image failed"<<std::endl;
        
        stbi_image_free(data);
    }
    return texu;
}
