#include "Texture.h"
#include <string>

// Constructorul: Inițializează variabilele membru și generează ID-ul texturii pe GPU
Texture::Texture() {
    this->width = 0;
    this->height = 0;
    this->Image_Format = GL_RGB;
    this->Internal_Format = GL_RGB;
    this->Filter_Max = GL_LINEAR;
    this->Filter_Min = GL_LINEAR;
    this->Wrap_S = GL_REPEAT;
    this->Wrap_T = GL_REPEAT;

    glGenTextures(1, &this->ID);
}

// 1. Funcția care încarcă pixelii efectivi în memoria plăcii video (VRAM)
void Texture::Generate(unsigned int width, unsigned int height, unsigned char* data) {
    this->width = width;
    this->height = height;

    // Activăm (bind-uim) textura curentă înainte de configurare
    glBindTexture(GL_TEXTURE_2D, this->ID);

    // Încărcăm datele imaginii în memoria GPU
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);

    // Setăm parametrii de Wrap (cum se repetă textura pe axele S și T)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);

    // Setăm parametrii de Filtrare (cum se scalează textura la zoom-in/zoom-out)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);

    // Facem unbind ca să nu modificăm textura accidental mai târziu
    glBindTexture(GL_TEXTURE_2D, 0);
}

// 2. Funcția care activează textura înainte de randarea unui obiect
void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, this->ID);
}