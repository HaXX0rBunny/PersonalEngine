#pragma once
#include <gl.h>

#include "../../Extern/image/stb_image.h"

#include <iostream>

class Texture {
    GLuint textureID;
    int width, height, channels;
 
    std::string filePath;
public:
    
    void LoadTexture();
    void UseTexture(); 
    void ClearTexture(); 
    unsigned char* GetData();
    void SetData(unsigned char* data_);

    Texture();
    Texture(const std::string& fileName);
    GLuint GetTextureID() const;
    ~Texture();
  

};  
void TextureUnload(Texture* texture);
