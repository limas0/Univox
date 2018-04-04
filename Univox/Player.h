#pragma once
#include "Header.h"
#include "EngineHeader.h"

class Player
{
public:
	Player();
	~Player();

	void create();
	void destroy();

	void update();

	WE::FirstPersonCamera *getCamera();
private:
	WE::FirstPersonCamera *camera = nullptr;
};

