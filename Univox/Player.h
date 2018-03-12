#pragma once
#include "Header.h"

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

