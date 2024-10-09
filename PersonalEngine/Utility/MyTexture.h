#pragma once
#include <gl.h>

#include "../../Extern/image/stb_image.h"

#include <iostream>

class Texture {
    GLuint textureID;
    int width, height, channels;
 
    std::string filePath;
public:
    
    void LoadTexture();// 디스크 저장된 이미지 메모리에 텍스쳐로 로드
    void UseTexture(); // 렌더링할때 이 텍스쳐 쓰겠다고 설정
    void ClearTexture(); // 메모리에서 텍스쳐 내리기
    unsigned char* GetData();
    void SetData(unsigned char* data_);
    // 생성자
    Texture(const std::string& fileName);
    GLuint GetTextureID() const;
    ~Texture();
  

};  
void TextureUnload(Texture* texture);
