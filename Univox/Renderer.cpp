#include "Renderer.h"
#include "Game.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::create()
{
	engine.create(GAME->getWindow());

	auto &renderer = engine.getRenderer();
	auto &context = engine.getContext();
	auto &sceneHandler = engine.getSceneHandler();
	auto &materialHandler = engine.getMaterialHandler();
	auto &materialLoader = engine.getMaterialLoader();

	viewport.create({ 0.f, 0.f }, { (float)GAME->getWindow().getWidth(), (float)GAME->getWindow().getHeight() }, { 0.f, 1.f });
	context.setViewport(viewport);

	renderer.setClearColor({ 1.f, 0.6f, 0.21f, 1.f });

	defaultStates = new WE::RenderStates();
	{
		WE::RasterizerState *rasterizerState = new WE::RasterizerState();
		rasterizerState->FillMode = D3D11_FILL_SOLID;
		rasterizerState->CullMode = D3D11_CULL_NONE;
		rasterizerState->create();
		defaultStates->setRasterizerState(rasterizerState);
	}

	wireframeStates = new WE::RenderStates();
	{
		WE::RasterizerState *rasterizerState = new WE::RasterizerState();
		rasterizerState->FillMode = D3D11_FILL_WIREFRAME;
		rasterizerState->CullMode = D3D11_CULL_NONE;
		rasterizerState->create();
		wireframeStates->setRasterizerState(rasterizerState);
	}

	{
		WE::InputLayout inputLayout;
		inputLayout.addElement({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		inputLayout.addElement({ "TEXCOORDS", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		inputLayout.addElement({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		inputLayout.addElement({ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		//inputLayout.addElement({ "BITANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		shader.load("../../WODXE11/resources/shaders/Standard", inputLayout, false);
	}

	static WE::Sampler sampler;
	sampler.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampler.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampler.MinLOD = 0;
	sampler.MaxLOD = D3D11_FLOAT32_MAX;
	sampler.create();

	textureAtlas.load("..\\bin\\mods\\Vanilla\\atlas.png");

	materialLoader.loadAllFrom("../resources/", &sampler);

	materialHandler.addMaterial("Wiremat", wireframeStates);
	materialHandler.getMaterial("Wiremat")->albedoValue = { 1.f, 1.f, 1.f };

	materialHandler.addMaterial("Default", defaultStates);
	materialHandler.getMaterial("Default")->albedoValue = { 0.f, 1.f, 0.5f };
	materialHandler.getMaterial("Default")->setAlbedoTexture(&textureAtlas, &sampler);
}

void Renderer::destroy()
{
	wireframeStates->destroy();
	defaultStates->destroy();

	shader.destroy();

	engine.destroy();
}

void Renderer::clear()
{
	engine.getRenderer().clear();
}

void Renderer::update()
{
	engine.update();
	engine.getRenderer().update();
}

void Renderer::render()
{
	//ImGui::Text("x: %f, y: %f, z: %f", XMVectorGetX(camera->getPosition()), XMVectorGetY(camera->getPosition()), XMVectorGetZ(camera->getPosition()));
	engine.getRenderer().render(defaultStates, &shader);
}

WE::Engine &Renderer::getEngine()
{
	return engine;
}
