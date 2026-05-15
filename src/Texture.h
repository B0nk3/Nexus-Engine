#ifndef TEXTURE_H
#define TEXTURE_H

#include "include/glad/glad.h"

class Texture{
    public:
    // ID of the texture object, used by OpenGL to reference this specific texture
        unsigned int ID;
        unsigned int width, height;
        
        // Format of the texture object
        unsigned int Internal_Format;
        // Format of the loaded source image
        unsigned int Image_Format;

        // S-axis (horizontal) wrapping mode
        unsigned int Wrap_S;
        // T-axis (vertical) wrapping mode
        unsigned int Wrap_T;
        // Filtering mode used when the texture is downscaled (minified)
        unsigned int Filter_Min;
        // Filtering mode used when the texture is upscaled (magnified)
        unsigned int Filter_Max;


        //constructor: initializes default texture settings
        Texture();

        // Generates the texture from image data
        // @param width: width of the image in pixels
        // @param height: height of the image in pixels
        // @param data: raw pixel data loaded from the image file
        void Generate(unsigned int width, unsigned int height, unsigned char* data);

        //binds the texture as the curent active GL_TEXTURE_2D object
        void Bind() const;
};
#endif