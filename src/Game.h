#ifndef GAME_H
#define GAME_H

#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "shader.h"
#include "SpriteRenderer.h"
#include  "ResourceManager.h"


enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game {
    public:
        GameState state;
        bool Keys[1024];
        unsigned int width, height;
        SpriteRenderer* renderer;
        Game(unsigned int width, unsigned int height);
        ~Game();
        void init();
        void Update(float deltaTime);
        void Render();
        void framebuffer_size_callback(GLFWwindow *window, int width, int height);
};
#endif