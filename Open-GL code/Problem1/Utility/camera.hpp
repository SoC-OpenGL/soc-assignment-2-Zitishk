#ifndef camera_hpp
#define camera_hpp

#include <iostream>

#include <math.h>
#include <vector>
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
struct Camera
{
    Camera(void);
    
    GLint WIDTH, HEIGHT;
    float fov;
    bool firstmouse;
    
    float lastX , lastY;
    
    glm::vec3 Campos;
    glm::vec3 Tarpos;
    glm::vec3 camUp;
    glm::vec3 right;
    
    glm::mat4 view();
    glm::mat4 proj();
    
    void proinp(GLFWwindow *window);
    void mousepro (double xpos, double ypos);


};
#endif /* camera_hpp */
