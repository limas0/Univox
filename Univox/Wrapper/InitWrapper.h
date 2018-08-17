#pragma once
#include "..\Registries\BlockRegistry.h"

class Game;

class UNIVOX_API InitWrapper
{
public:
	InitWrapper();
	~InitWrapper();

	void create();
	void destory();

	BlockRegistry &getBlockRegistry();

	BlockRegistry *p_blockRegistry = nullptr;
};