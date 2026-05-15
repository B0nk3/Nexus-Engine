#include "Game.h"
#include <GLFW/glfw3.h>


Game::Game(unsigned int width,unsigned int height){
    this-> width = width;
    this-> height = height;
    glViewport(0, 0, width, height);
}

Game::~Game(){
    
}

void Game::framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
    this-> width = width;
    this-> height = height;
}

void Game::Render(){
    //Clearing the screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    if(this->state == GAME_ACTIVE){
        
    }
}

void Game::init(){
    ResourceManager::LoadShader("C:\\Users\\LENOVO\\Downloads\\Aura-Engine-main\\shaders\\shader.vs", "C:\\Users\\LENOVO\\Downloads\\Aura-Engine-main\\shaders\\shader.fs", "sprite");

    glm::mat4 projection = glm::ortho(0.0f, (float)this->width, (float)this->height, 0.0f, -1.0f, 1.0f);
    Shader &s = ResourceManager::GetShader("sprite");

    s.use(); 
    s.setInt("image", 0); 
    s.setMatrix4f("projection", projection);

}