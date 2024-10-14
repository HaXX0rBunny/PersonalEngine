#include "TextResource.h"
#include "../Utility/MyTexture.h"
void TextResource::Load(const std::string& filename)      
{
	Texture* texture = new Texture(filename);

	std::cout << "TextResource 7: Created Texture at " << texture << std::endl;
	texture->LoadTexture();
	data = texture;

}

void TextResource::Unload()      
{
	if (data != nullptr)
	{
		TextureUnload(static_cast<Texture*> (data));
		data = nullptr;
		counter--;
	}
}
 
void* TextResource::GetData() const      
{
	return data;
}

