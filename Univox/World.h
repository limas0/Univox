#pragma once
#include "Header.h"

class World
{
public:
	World();
	~World();

	void create();
	void destroy();
private:
	WE::Scene *scene = nullptr;
};

