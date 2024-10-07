
#include "MyTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../Extern/image/stb_image.h"
#undef STB_IMAGE_IMPLEMENTATION
Texture::Texture(const std::string& fileName)
	: textureID(0), width(0), height(0), channels(0), data(nullptr) // ��� ���� �ʱ�ȭ
{
	filePath = fileName; // ���� ��θ� filePath�� ����
}
Texture::~Texture()
{
	ClearTexture();
}

void Texture::LoadTexture()
{
	data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	// �̹��� �����͸� �������� ���� (��ε忡�� ó��)
}

void Texture::UseTexture()
{
	glActiveTexture(GL_TEXTURE0); //0�� �ؽ��� ���� Ȱ��ȭ
	glBindTexture(GL_TEXTURE_2D, textureID); // VRAM ���� �ִ� �� �ؽ��ĸ� 0�� �ؽ��� ���ֿ� bind

}

void Texture::ClearTexture()
{
	if (textureID) {
		glDeleteTextures(1, &textureID); // OpenGL �ؽ�ó ����
		textureID = 0;
	}
	if (data) {
		stbi_image_free(data); // �̹��� ������ ����
		data = nullptr;
	}
}

unsigned char* Texture::GetData()
{
	return data;
}

void Texture::SetData(unsigned char* data_)
{
	data = data_;
}

void TextureUnload(Texture* texture)
{

	if (texture) {
		texture->ClearTexture();
		delete texture; // ���� �Ҵ�� ��ü ����
		std::cout << "Texture memory has been freed." << std::endl;
	}

}
