
#include "camera.hpp"
#include <iostream>

#include <math.h>
#include <vector>
#include <string>
// Shader class , camera and cube contains vertex information
#include "shader.hpp"

#include "cube.hpp"

#include "texturing.hpp"
// Used for matrice and vector operations

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

Camera:: Camera(void)
{
    WIDTH = 600;
    HEIGHT = 600;
    fov =0.0f;
    firstmouse = true;
    yaw=-90.0f;
    pitch=0.0f;
    uprotation=0.0f;
    
    lastX = WIDTH/2.0f;
    lastY = HEIGHT/2.0f;
    
    Campos = glm::vec3(0.0f,0.0f,3.0f);
    Tarpos = glm::vec3(0.0f,0.0f,-1.0f);
    camUp  = glm::vec3(0.0f, 1.0f,  0.0f);
    right = glm::cross(Tarpos-Campos,camUp);
    
}

void Camera:: proinp(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    const float cameraSpeed = 0.01f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Campos += glm::normalize(Tarpos) * cameraSpeed * 5.0f;
    
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Campos -= glm::normalize(Tarpos)*cameraSpeed*5.0f ;
    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Campos -= glm::normalize(glm::cross(Tarpos, camUp)) * cameraSpeed * 5.0f;
    
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Campos += glm::normalize(glm::cross(Tarpos, camUp)) * cameraSpeed*5.0f;
    
    
    
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        
        uprotation+= 0.3f;
        if (uprotation>179.0f)
            uprotation =179.0f;
        else if (uprotation<-179.0f)
            uprotation =-179.0f;
        else
        {
        float ro =0.0f;
        ro+=0.3f;
        glm::vec4 temp= glm::vec4(camUp,1.0f);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, glm::radians(ro), glm::vec3(0.0, 0.0, 1.0));
        temp = trans*temp;
        
        camUp= glm::vec3(temp.x,temp.y,temp.z);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        
        uprotation-= 0.3f;
        if (uprotation>179.0f)
            uprotation =179.0f;
        else if (uprotation<-179.0f)
            uprotation =-179.0f;
        else
        {
        float ro =0.0f;
        ro-=0.3f;
        glm::vec4 temp= glm::vec4(camUp,1.0f);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, glm::radians(ro), glm::vec3(0.0, 0.0, 1.0));
        temp = trans*temp;
        
        camUp= glm::vec3(temp.x,temp.y,temp.z);
        }
    }
    
    
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        if (fov<20.f)
            fov+=1.0f;
    }
    
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        if (fov>-20.f)
            fov-=1.0f;
    }
}

void Camera:: mousepro (double xpos, double ypos)
{
    if(firstmouse) // initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstmouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;
    
    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    yaw   += xoffset;
    pitch += yoffset;
    
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    glm::vec4 temp= glm::vec4(direction,1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(uprotation), glm::vec3(0.0, 0.0, 1.0));
    temp = trans*temp;
    
    direction= glm::vec3(temp.x,temp.y,temp.z);
    
    Tarpos = glm::normalize(direction);
}
glm::mat4 Camera:: view()
{
    glm::mat4 view=glm::mat4(1.0f);
    view = glm::lookAt(Campos,Campos + Tarpos, camUp);
    return view;
}

glm::mat4 Camera:: proj()
{
    glm::mat4 proj = glm::mat4(1.0f);
    proj =glm::perspective(glm::radians(45.0f+fov), 600.0f/600.0f, 0.1f, 100.0f);
    return proj;
}

