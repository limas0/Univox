#pragma once
#include "Mod.h"

class ModHandler
{
public:
	ModHandler();
	~ModHandler();

	void destroy();

	void registerMod(Mod *mod);

private:
	std::list<Mod*> mods;
};
