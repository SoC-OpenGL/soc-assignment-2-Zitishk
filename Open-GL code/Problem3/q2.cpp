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

void proinp(GLFWwindow* window);

int a=1;

bool bkeypress=false;
bool Bling = true;


struct Light
{
    glm::vec3 Pos;
    glm::vec3 color;
    Light()
    {
        Pos = glm::vec3(2.0f,1.0f,10.0f);
        color = glm::vec3(1.0f,1.0f,1.0f);
    }
};

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
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    glewExperimental = GL_TRUE;
    glewInit();
    

    cube box;
    cube skybox(1,0);
    Light lig;
    //Material mat;
    glEnable(GL_DEPTH_TEST);
    
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
    
    
    ShaderProgram *shdr = new ShaderProgram("shaders/shad.vs","shaders/shad.fs");
    Texture *alb = new Texture("Images/brick/albedo.jpg",false);
    Texture *spe = new Texture("Images/brick/specular.png",true);
    Texture *ao = new Texture("Images/brick/ao.jpg",false);
    Texture *norm = new Texture("Images/brick/normal.jpg",false);

    //Texture *alb = new Texture("Images/a.jpg",false);
    //Texture *norm = new Texture("Images/an.jpg",false);
    
    shdr->Use();
    shdr->setint("alb",0);
    shdr->setint("spe",1);
    shdr->setint("norm",2);
    shdr->setint("ao",3);
     
    
    ShaderProgram YAGAMI ( "shaders/shadlight.vs", "shaders/shadlight.fs");
    
    
    
    while (!glfwWindowShouldClose(window))
    {
        
        float currentframe = glfwGetTime();
        deltaTime=currentframe-lastframe;
        lastframe=currentframe;
 
        //TO PROCESS INP RELATED TO CAM
        Cam.proinp( window);
        
        proinp (window);
        
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        shdr->Use();
         
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = Cam.view();
        glm::mat4 projection = Cam.proj();
        model=glm::scale(model,glm::vec3(1.0f));
        
        
        shdr->setmat4("model", model);
        shdr->setmat4("view", view);
        shdr->setmat4("projection", projection);
        shdr->setvec3("ligpos",lig.Pos);
        shdr->setlight("lig",lig.color,lig.Pos);
        shdr->setvec3("cpos",Cam.Campos);
        alb->use(0);
        spe->use(1);
        norm ->use(2);
        ao->use(3);
        shdr->setint("a",a);
        shdr->setint("Bling",Bling);
        
        // cubes
        glBindVertexArray(box.VAO);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        
        
        
        
        if(a!=0)
        {
        
            YAGAMI.Use();
            glBindVertexArray(skybox.VAO);
            
            YAGAMI.setmat4("view", view);
            YAGAMI.setmat4("projection", projection);
            
            model=glm::translate(model,lig.Pos);
            model=glm::scale(model,glm::vec3(0.3f));
            YAGAMI.setmat4("model", model);
            YAGAMI.setvec3("lightColor",lig.color);
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        
        }
        
        
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

void proinp(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        a=0;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        a=1;
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        a=2;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && !bkeypress)
    {
        Bling = !Bling;
        bkeypress = true;
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE)
    {
        bkeypress = false;
    }
}
