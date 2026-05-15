#include <map>
#include <string>
#include "ResourceManager.h"
#include "Texture.h"

#include "stb_image.h"
std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture> ResourceManager::textures;

Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name){
    Shader shader(vShaderFile, fShaderFile);
    shaders[name] = shader;
    return shaders[name];
}

Shader& ResourceManager::GetShader(std::string name){
    return shaders[name];
}

Texture ResourceManager::LoadTexture(const char *file, bool alpha, std::string name)
{
    // Apelează funcția privată de încărcare de pe disc
    textures[name] = loadTextureFromFile(file, alpha);
    
    // Returnează textura proaspăt salvată în map
    return textures[name];
}


Texture ResourceManager::loadTextureFromFile(const char *file, bool alpha)
{
    // 1. Creează obiectul Texture2D gol (care are setările default)
    Texture texture;
    
    if (alpha)
    {
        // Dacă imaginea are transparență (PNG), schimbăm formatele înainte de generare
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    
    // 2. Încarcă datele imaginii de pe disc în RAM folosind stb_image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    
    // 3. Generăm textura pe GPU dacă citirea fișierului a reușit
    if (data)
    {
        texture.Generate(width, height, data);
    }
    else
    {
        std::cout << "Failed to load texture at: " << file << std::endl;
    }
    
    // 4. Eliberează memoria RAM ocupată de pixeli (acum sunt salvați în VRAM pe placa video)
    stbi_image_free(data);
    
    return texture;
}