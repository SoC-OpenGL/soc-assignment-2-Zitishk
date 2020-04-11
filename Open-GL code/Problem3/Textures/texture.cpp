
#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture(const char* imgpath,bool alpha)
{
    
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
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        
        if(alpha)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pwidth, pheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pwidth, pheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else std:: cout<<"image failed"<<std::endl;
    
    stbi_image_free(data);
    
}


void Texture::use(int i)
{
    glActiveTexture(GL_TEXTURE0+i);
    glBindTexture(GL_TEXTURE_2D, tex);
}
