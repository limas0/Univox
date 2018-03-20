#include "Game.h"
#include "World\Chunk\ChunkMeshBuilder.h"
#include "World\Chunk\ChunkMesh.h"

Game *Game::game = nullptr;

Game::Game()
{
	Game::game = this;
}

Game::~Game()
{
}

void Game::create()
{
	window.create("Univox", 1280, 720);
	renderer.create();

	auto &sceneHandler = renderer.getEngine().getSceneHandler();

	worldRenderer.create(sceneHandler.addScene("World"));
	sceneHandler.setActiveScene(worldRenderer.getScene());

	player.create();
	worldRenderer.getScene()->setActiveCamera(player.getCamera());

	world.create();

	{
		Vec2i pos(0, 0);

		Chunk *chunk = new Chunk();
		chunk->create(pos);

		world.setChunk(pos, chunk);

		ChunkMesh *chunkMesh = new ChunkMesh();
		ChunkMeshBuilder(chunk, chunkMesh).build();
		chunkMesh->create();

		chunkMesh->setMaterial("Default");
		chunkMesh->setTranslation({ float(pos.x * Consts::CHUNK_SIZE), 0.f, float(pos.y * Consts::CHUNK_SIZE) });

		worldRenderer.setChunkMesh(pos, chunkMesh);
	}
}

void Game::destroy()
{
	world.destroy();
	player.destroy();
	worldRenderer.destroy();
	renderer.destroy();
	window.destroy();
}

void Game::run()
{
	while (window.isOpen())
	{
		while (window.peekMessage(msg))
		{
			if (msg.is(WM_QUIT))
				window.close();
		}

		renderer.clear();
		renderer.update();
		player.update();

		world.update();
		renderStats.update();
		renderStats.draw();

		ImGui::SetNextWindowBgAlpha(0.f);
		ImGui::SetNextWindowSize(ImVec2(float(window.getWidth()), float(window.getHeight())));
		ImGui::SetNextWindowPos(ImVec2(-5.f, -5.f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
		ImGui::Begin("Top left info", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
		ImGui::Text("FPS: %i (%.3f ms)", renderer.getEngine().getFrameProfiler().getFPSCount(), renderer.getEngine().getFrameProfiler().getDeltaTimeAvg());
		ImGui::Text("DeltaTime: %f s", renderer.getEngine().getFrameProfiler().getDeltaTime());
		ImGui::End();
		ImGui::PopStyleVar(1);

		renderer.render();
	}
}

WE::Window &Game::getWindow()
{
	return window;
}

Renderer &Game::getRenderer()
{
	return renderer;
}

Player &Game::getPlayer()
{
	return player;
}

World &Game::getWorld()
{
	return world;
}

WorldRenderer &Game::getWorldRenderer()
{
	return worldRenderer;
}
