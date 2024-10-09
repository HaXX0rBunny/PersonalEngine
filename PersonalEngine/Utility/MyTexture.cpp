
#include "MyTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../Extern/image/stb_image.h"
#undef STB_IMAGE_IMPLEMENTATION
Texture::Texture(const std::string& fileName)
	: textureID(0), width(0), height(0), channels(0) // ��� ���� �ʱ�ȭ
{
	filePath = fileName; // ���� ��θ� filePath�� ����
}
Texture::~Texture()
{
	ClearTexture();
}

void Texture::LoadTexture()
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char * data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

	if (!data)
	{
		std::cerr << "Failed to load texture file: " << filePath << std::endl;
	}
	else {
		std::cout << "Loaded texture: " << filePath << ", Size: "
			<< width << "x" << height << ", Channels: " << channels << std::endl;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		// �ؽ�ó ������ ���ε�
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data); // �̹��� ������ ����
		data = nullptr;

	}

}


void Texture::UseTexture()
{
	glActiveTexture(GL_TEXTURE0); // 0�� �ؽ�ó ���� Ȱ��ȭ
	glBindTexture(GL_TEXTURE_2D, textureID); // VRAM ���� �ִ� �� �ؽ�ó�� 0�� �ؽ�ó ���ֿ� ���ε�
}

void Texture::ClearTexture()
{
	if (textureID) {
		glDeleteTextures(1, &textureID); // OpenGL �ؽ�ó ����
		textureID = 0;
	}

}




GLuint Texture::GetTextureID() const
{
	return textureID;
}
void TextureUnload(Texture* texture)
{

	if (texture) {
		texture->ClearTexture();
		//delete texture; // ���� �Ҵ�� ��ü ����

		std::cout << "Texture memory has been freed." << std::endl;
	}

}
