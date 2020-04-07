#include <iostream>

#include <math.h>
#include <vector>
#include <string>
// Shader class , camera and cube contains vertex information
#include "Utility/shader.hpp"
#include "Utility/camera.hpp"
#include "Utility/cube.hpp"

#include "Utility/texturing.hpp"
// Used for matrice and vector operations

#include "Utility/glm/glm.hpp"
#include "Utility/glm/gtc/matrix_transform.hpp"
#include "Utility/glm/gtc/type_ptr.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>


// SIZE OF WINDOW
const GLint WIDTH = 600, HEIGHT = 600;


float fov =0.0f;
bool firstmouse = true;

float lastX = WIDTH/2.0f, lastY = HEIGHT/2.0f;

glm::vec3 Campos = glm::vec3(0.0f,0.0f,0.5f);
glm::vec3 Tarpos = glm::vec3(0.0f,0.0f,-1.0f);
glm::vec3 camUp  = glm::vec3(0.0f, 1.0f,  0.0f);
glm::vec3 right = glm::cross(Tarpos-Campos,camUp);


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
    cube cube2(2.0f);
    
    GLuint text1 = texture("Images/tex.jpg");
 
    ShaderProgram Shaeder("Shaders/shadercube.vs","Shaders/shadercube.fs");
    
    // matrice controling the position of object
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f,0.0f,0.0f));

    Shaeder.Use();
    Shaeder.setmat4("model", model);
    
    while( !glfwWindowShouldClose( window ))
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        
        glClear( GL_COLOR_BUFFER_BIT);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        Cam.proinp( window );
        
        Shaeder.Use();
        
        glm::mat4 view=glm::mat4(1.0f);
        view = Cam.view();
        
        glm::mat4 proj = glm::mat4(1.0f);
        proj = Cam.proj();
        
        Shaeder.setmat4("view", view);
        Shaeder.setmat4("proj", proj);

        glBindTexture(GL_TEXTURE_2D, text1);
        
        glBindVertexArray(cube1.VAO);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);

        
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
