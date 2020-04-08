#include <iostream>

#include <math.h>
#include <vector>
#include <string>


// Shader class , camera and cube contains vertex information

#include "Utility/shader.hpp"
#include "Utility/camera.hpp"
#include "Utility/cube.hpp"

//#include "skybox.hpp"
//#include "texturing.hpp"
// Used for matrice and vector operations

#include "Utility/glm/glm.hpp"
#include "Utility/glm/gtc/matrix_transform.hpp"
#include "Utility/glm/gtc/type_ptr.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "Utility/stb_image.h"



// SIZE OF WINDOW
const GLint WIDTH = 600, HEIGHT = 600;

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
     "Images/tex.jpg",
     "Images/tex.jpg",
     "Images/tex.jpg",
     "Images/tex.jpg",
     "Images/tex.jpg",
     "Images2/tex.jpg"
     };
    
    
     for(int i=0;i<6;i++)
     {
     int pwidth, pheight, nrChannels;
     //stbi_set_flip_vertically_on_load(true);
     unsigned char *data = stbi_load(faces[i].c_str(), &pwidth, &pheight, &nrChannels,0);
     
     if(data)
     {
         glPixelStorei(GL_UNPACK_ALIGNMENT,1);
         glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, pwidth, pheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
     }
     else std:: cout<<"image failed"<<std::endl;
     
     stbi_image_free(data);
     }
 
    return texu;
}

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

// to vary the size of window
void framebuffer_size_callback(GLFWwindow *window,int width,int height)
{
    glViewport(0, 0, width, height);
}

// function to process mouse

void mousepro (GLFWwindow *window,double xpos, double ypos);
// function to process the input
// defined at last of file

Camera Cam;

int main ()
{
    //INITIALIZING GLFW,
    
    glfwInit();
    
    
    //SETTING UP GLFW,
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_TRUE );
    
    
    //CREATING THE WINDOW
    
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Ass2", NULL, NULL);
    
    //CHECK SUCCESS
    if (window == NULL)
    {
        
        std::cout<<"Failed "<< std::endl;
        glfwTerminate();
        return -1;
    
    }
    
    glfwMakeContextCurrent( window );
    
    glewExperimental = GL_TRUE;
    
    
    if (GLEW_OK != glewInit())
    {
        std::cout<<"Failed "<< std::endl;
        return -1;
    }
    
    //getting the changed size of window
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window,&screenWidth, &screenHeight );
    
    //setting the viewing window
    glViewport(0, 0, screenWidth, screenHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    //To make sure only the closest part is visible
    glEnable(GL_DEPTH_TEST);
    
    
    //hides the cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mousepro);
    
    
    cube cube1;

    cube sky(1.0f,0);
    
    GLuint text1 = texture("Images/tex.jpg");

    ShaderProgram Skyp ("shaders/shadercube.vs" ,"shaders/shadercube.fs");
    
    ShaderProgram Shaeder ( "shaders/shadsky.vs", "shaders/shadsky.fs");


    GLuint skyt = skox();
    
    // matrice controling the position of object
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f,0.0f,0.0f));

    Skyp.Use();
    Skyp.setmat4("model", model);
    
    while( !glfwWindowShouldClose( window ))
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        
        glClear( GL_COLOR_BUFFER_BIT);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        Cam.proinp( window );
        
        Skyp.Use();
        
        glm::mat4 view=glm::mat4(1.0f);
        view = Cam.view();
        
        glm::mat4 proj = glm::mat4(1.0f);
        proj = Cam.proj();
        
        Skyp.setmat4("view", view);
        Skyp.setmat4("proj", proj);
        
        glBindVertexArray(cube1.VAO);
        
        glBindTexture(GL_TEXTURE_2D, text1);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        
        glBindVertexArray(0);
        
        glDepthFunc(GL_LEQUAL);
        Shaeder.Use();
        
        view = glm::mat4(glm::mat3(view));
        
        Shaeder.setmat4("view", view);
        Shaeder.setmat4("proj", proj);

        
        glBindVertexArray(sky.VAO);
        
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyt);

        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);
        
        
        
        glfwSwapBuffers( window);
        glfwPollEvents( );
    }
    
    
    glfwTerminate( );
    return 0;
}

void mousepro (GLFWwindow *window,double xpos, double ypos)
{
    Cam.mousepro( xpos, ypos);
}

