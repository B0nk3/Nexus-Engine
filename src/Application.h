#ifndef APPLICATION_H
#define APPLICATION_H

#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "Shader.h"

class Application {
    public:
        GLFWwindow *window;
        unsigned int width, height;
        bool keys[1024];
        //constructor and destructor
        Application(unsigned int width, unsigned int height);
        ~Application();
        Application();
        
        bool init();
        void ProcessInput(float dt);
        void Update(float dt);
        void Render();

        unsigned int Width, Height;
        Shader* myShader;
};

#endif