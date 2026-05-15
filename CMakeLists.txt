cmake_minimum_required(VERSION 3.15)
project(GameEngine)

set(CMAKE_CXX_STANDARD 17)

# Descarcă GLFW automat
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.3.8
)

include_directories(include)

# Oprim setările inutile de la GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

# Executabilul tău cu TOATE fișierele originale
add_executable(GameEngine 
    src/main.cpp 
    src/glad.c 
    src/Shader.cpp 
    src/Application.cpp 
    src/Application.h
    src/Game.h 
    src/Game.cpp 
    src/Camera2D.h 
    src/Camera2D.cpp
    src/ResourceManager.h
    src/ResourceManager.cpp
    src/SpriteRenderer.h
    src/SpriteRenderer.cpp
    src/Texture.h
    src/Texture.cpp

)

# Unde este folderul include
target_include_directories(GameEngine PRIVATE 
    include
    ${CMAKE_SOURCE_DIR}/include
)

# Legătură GLFW
target_link_libraries(GameEngine PRIVATE glfw)