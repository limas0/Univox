#pragma once
#include "..\Header.h"
#include <SFML\Graphics.hpp>

struct TextureBounds
{
	float x = 0;
	float y = 0;
	float w = 0;
	float h = 0;

	TextureBounds()
	{
	}

	TextureBounds(float x, float y, float w, float h) :
		x(x), y(y), w(w), h(h)
	{
	}
};

struct Node
{
	TextureBounds bounds;
	Node *left = nullptr;
	Node *right = nullptr;
	bool filled = false;

	Node(TextureBounds &bounds)
	{
		this->bounds = bounds;
	}

	~Node()
	{
		if (left)
			delete left;
		left = nullptr;
		if (right)
			delete right;
		right = nullptr;
	}

	TextureBounds *insert(TextureBounds &input)
	{
		if (left || right)
		{
			TextureBounds *leftRect = left->insert(input);
			if (!leftRect)
				return right->insert(input);
			return leftRect;
		}
		else
		{
			if (filled || input.w > bounds.w || input.h > bounds.h)
				return nullptr;

			if (input.w == bounds.w && input.h == bounds.h)
			{
				filled = true;
				return &bounds;
			}

			int diffX = bounds.w - input.w;
			int diffY = bounds.h - input.h;

			TextureBounds leftRect(bounds);
			TextureBounds rightRect(bounds);

			if (diffX > diffY)
			{
				leftRect.w = input.w;
				rightRect.x += input.w;
				rightRect.w -= input.w;
			}
			else
			{
				leftRect.h = input.h;
				rightRect.y += input.h;
				rightRect.h -= input.h;
			}

			left = new Node(leftRect);
			right = new Node(rightRect);

			return left->insert(input);
		}
	}
};

class UNIVOX_API TextureAtlas
{
public:
	TextureAtlas();
	~TextureAtlas();

	void create();
	void destroy();

	void generateAtlas();

	void insertTexture(std::string path);

private:
	Node *atlasRoot = nullptr;
	sf::Image atlasTexture;

	std::vector<sf::Image> textures;

};