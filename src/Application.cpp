#include <stdio.h>
#include "Application.h"

Application::Application(unsigned int width, unsigned int height){
   
    this->width = width;
    this->height = height;
    this->window = nullptr;
}

Application::Application(){
    this->window = nullptr;
    this->width = 800;
    this->height = 600;
}

Application::~Application(){
    glfwDestroyWindow(this->window);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS){

    }
        
}


void Application::ProcessInput(float dt){
    if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        //Application::~Application();
    }

    if(glfwGetKey(this->window, GLFW_KEY_E) == GLFW_PRESS){
        printf("A fost apasata tasta E \n");
    }
}

bool Application::init(){
    if(!glfwInit()){
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(width, height, "Fereastra de Test",NULL , NULL);

    if (!this->window) {
        // Dacă window e NULL, aflăm DE CE
        const char* description;
        int code = glfwGetError(&description);
        std::cout << "GLFW Error (" << code << "): " << description << std::endl;
        glfwTerminate();
        return false;
    }
    // 1. Facem contextul ferestrei curent pe thread-ul acesta
    glfwMakeContextCurrent(window);

    // 2. Inițializăm GLAD
    // glfwGetProcAddress este funcția GLFW care găsește locația funcțiilor OpenGL pe OS-ul tău
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}


void framebufer_size_callback(unsigned int width, unsigned int height){
    glViewport(0, 0, width, height);
}