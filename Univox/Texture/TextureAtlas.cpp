#include "TextureAtlas.h"

TextureAtlas::TextureAtlas()
{
}

TextureAtlas::~TextureAtlas()
{
	if (atlasRoot)
		delete atlasRoot;
	atlasRoot = nullptr;
}

void TextureAtlas::create()
{
	atlasTexture.create(512, 512);
	atlasRoot = new Node(TextureBounds(0, 0, 512, 512));

	for (int i = 0; i < 1024; i++)
	{
		textures.push_back(sf::Image());
		textures.back().loadFromFile("..\\bin\\mods\\Vanilla\\hardened_clay(" + std::to_string(i % 16) + ").png");
		auto rect = atlasRoot->insert(TextureBounds(0, 0, textures.back().getSize().x, textures.back().getSize().y));

		if(rect)
			atlasTexture.copy(textures.back(), rect->x, rect->y);
	}

	atlasTexture.saveToFile("..\\bin\\mods\\Vanilla\\atlas.png");
}

void TextureAtlas::destroy()
{
	
}

void TextureAtlas::generateAtlas()
{
	
}

void TextureAtlas::insertTexture(std::string path)
{
	textures.emplace_back();
	textures.back().loadFromFile(path);
}
