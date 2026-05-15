
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Game.h"
#include "Application.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}



int main() {
    Application application(800, 600);
    if(!application.init()){
        perror("ERROR::Aplication could not initialize \n");
        return -1;
    }
    
    Game NexusGame(800,600);
    NexusGame.init();


    float dt = 0.0f;
    float lastFrame = 0.0f;

    // --- 4. RENDER LOOP ---
    while(!glfwWindowShouldClose(application.window))
    {
        float currentFrame = glfwGetTime();

        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        application.ProcessInput(dt);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        NexusGame.Render();

        glfwSwapBuffers(application.window);
    }

    // --- 5. CLEAN UP RESOURCES ---
    glfwTerminate();
    return 0;
}