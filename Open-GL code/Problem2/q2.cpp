

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>


#include "utility/shader.hpp"
#include "Textures/texture.hpp"
#include "utility/camera.hpp"
#include "utility/cube.hpp"

#include "utility/glm/glm/glm.hpp"
#include "utility/glm/glm/gtc/matrix_transform.hpp"
#include "utility/glm/glm/gtc/type_ptr.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);


Camera Cam;


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Cam.mousepro(xpos,ypos);
}



unsigned int loadCubemap(std::vector<std::string> faces);
// settings
float deltaTime= 0.0f;
float lastframe=0.0f;
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;



int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
    
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cube", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    cube cube1;
    
    cube skybox(1.0f,0);
    
 
    glEnable(GL_DEPTH_TEST);
    
    //ShaderProgram *skyboxshdr = new ShaderProgram("shaders/shadsky.vs", "shaders/shadsky.fs");

    ShaderProgram skyboxshdr("shaders/shadsky.vs", "shaders/shadsky.fs");
    

    std::string arr[] = {
        "Images/skybox/right.jpg",
        "Images/skybox/left.jpg",
        "Images/skybox/top.jpg",
        "Images/skybox/bottom.jpg",
        "Images/skybox/front.jpg",
        "Images/skybox/back.jpg"
    };
    std::vector<std::string> faces(arr, arr + sizeof(arr)/ sizeof(std::string));
    unsigned int cubemapTexture = loadCubemap(faces);
    
    skyboxshdr.Use();
    skyboxshdr.setint("skybox", 0);
    
    ShaderProgram *shdr = new ShaderProgram("shaders/shad2.vs","shaders/shad.fs");
    Texture *txt = new Texture("Images/F.jpg");
    
    shdr->Use();
    shdr->setint("txt",0);
    while (!glfwWindowShouldClose(window))
    {
        
        float currentframe = glfwGetTime();
        deltaTime=currentframe-lastframe;
        lastframe=currentframe;
 
        
        Cam.proinp( window);
        
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        shdr->Use();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = Cam.view();
        glm::mat4 projection = Cam.proj();
        shdr->setmat4("model", model);
        shdr->setmat4("view", view);
        shdr->setmat4("projection", projection);
        // cubes
        glBindVertexArray(cube1.VAO);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        
        // draw skybox as last
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxshdr.Use();
        view = glm::mat4(glm::mat3(Cam.view())); // remove translation from the view matrix
        skyboxshdr.setmat4("view", view);
        skyboxshdr.setmat4("projection", projection);
        // skybox cube
        glBindVertexArray(skybox.VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
    
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}



unsigned int loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    
    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                         );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    return textureID;
}

