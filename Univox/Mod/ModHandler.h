#pragma once
#include "Mod.h"

class ModHandler
{
public:
	ModHandler();
	~ModHandler();

	void destroy();

	void registerMod(Mod *mod);

	void loadAll();
	void initAll();

private:
	std::list<Mod*> mods;
};
