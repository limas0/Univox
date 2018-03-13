#include "Game.h"

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
	player.create();

	world.create();
}

void Game::destroy()
{
	world.destroy();
	player.destroy();
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
		ImGui::SetNextWindowSize(ImVec2(window.getWidth(), window.getHeight()));
		ImGui::SetNextWindowPos(ImVec2(-5.f, -5.f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
		ImGui::Begin("okno", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
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
