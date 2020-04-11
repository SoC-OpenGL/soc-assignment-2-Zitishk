#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "stb_image.h"

class Texture{
	GLuint tex;
	int ID;
	public:
		int width, height, nrChannels;
        Texture( const char *Filename,bool alpha);

		void use(int i=0);

};
#endif
