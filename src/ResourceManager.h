#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include "include/glad/glad.h"
#include "Shader.h"
#include "Texture.h"
class ResourceManager{
    public:

        static std::map<std::string, Shader> shaders;
        static std::map<std::string, Texture> textures;

        //loat and return a shader
        static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name);

        //get an already loaded shader
        static Shader& GetShader(std::string name);
        //load and return a texture
        static Texture LoadTexture(const char *file, bool alpha, std::string name);
        //get an already loaded texture
        static Texture GetTexture(std::string name);

        static Texture loadTextureFromFile(const char *file, bool alpha);
        //clear memory
        static void Clear();
    private:
        ResourceManager();
};

#endif