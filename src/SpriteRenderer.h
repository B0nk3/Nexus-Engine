#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "include/glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "Texture.h"

class SpriteRenderer{
public:
    Shader shader;
          
    //vertex array object ID used for drwaing a simple 2D quad(square)
    unsigned int quadVAO;
    //constructor: recieves shader that will be used to draw sprites
    SpriteRenderer(Shader &shader);

    //destructor: cleans up allocated VAO/VBO on the GPU
    ~SpriteRenderer();

    void DrawSprite(Texture &texture, glm::vec2 position,
    glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
    glm::vec3 color = glm::vec3(1.0f));
    //initializes the vertex data and buffed configurations on the gpu
    void initRenderData();
 


};

#endif