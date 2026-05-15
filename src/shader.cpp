#include <fstream>
#include <sstream>
#include <string>
#include "shader.h"
#include <glm/gtc/type_ptr.hpp>


Shader::Shader(const char* vertexPath, const char* fragmentPath){
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    //ensure ifstream objects can throw exception
    try{
        //open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        if(!vShaderFile.is_open()){
            std::cout<< "ERROR: could not open vertex shader file"<<std::endl;
        }
        if(!fShaderFile.is_open()){
            std::cout<< "ERROR: could not open fragment shader file"<<std::endl;
        }
        std::stringstream vShaderStream, fShaderStream;

        //read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        //close file handlers
        vShaderFile.close();
        fShaderFile.close();
        //convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout <<  "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;

    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();



    //2. copmile shaders

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    //vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    //print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<< infoLog<<std::endl;
    };
    //fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    //print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout<<"ERROR::FRAGEMNT::SHADER::COMPILATION_FAILED\n"<< infoLog<<std::endl;
    }


    //shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    //print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<< infoLog<< std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMatrix4f(const char* name, const glm::mat4& matrix) {
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::setVector3f(const char* name, const glm::vec3& value) {
    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}