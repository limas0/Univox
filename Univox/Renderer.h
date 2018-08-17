#pragma once
#include "Header.h"
#include "EngineHeader.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void create();
	void destroy();

	void clear();
	void update();
	void render();

	WE::Engine &getEngine();

private:
	WE::Engine engine;
	WE::Viewport viewport;
	WE::Shader shader;

	WE::RenderStates *defaultStates = nullptr;
	WE::RenderStates *wireframeStates = nullptr;

	WE::Texture textureAtlas;
};

