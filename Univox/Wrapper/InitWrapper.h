#pragma once
#include "..\Registries\BlockRegistry.h"

class Game;

class UNIVOX_API InitWrapper
{
public:
	InitWrapper();
	~InitWrapper();

	void create(Game *instance);
	void destory();

	BlockRegistry &getBlockRegistry();

private:
	Game *p_game = nullptr;
};