#pragma once
#include <gl.h>

#include "../../Extern/image/stb_image.h"

#include <iostream>

class Texture {
    GLuint textureID;
    int width, height, channels;
 
    std::string filePath;
public:
    
    void LoadTexture();// ��ũ ����� �̹��� �޸𸮿� �ؽ��ķ� �ε�
    void UseTexture(); // �������Ҷ� �� �ؽ��� ���ڴٰ� ����
    void ClearTexture(); // �޸𸮿��� �ؽ��� ������
    unsigned char* GetData();
    void SetData(unsigned char* data_);
    // ������
    Texture(const std::string& fileName);
    GLuint GetTextureID() const;
    ~Texture();
  

};  
void TextureUnload(Texture* texture);
