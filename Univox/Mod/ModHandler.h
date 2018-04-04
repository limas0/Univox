#pragma once
#include "Mod.h"

class InitWrapper;

class UNIVOX_API ModHandler
{
public:
	ModHandler();
	~ModHandler();

	void destroy();

	void registerMod(Mod *mod);

	void loadAll();
	void initAll(InitWrapper *wrapper);

	//Returns nullptr if no mod is being used
	inline Mod *getCurrentlyUsedMod();

private:
	std::list<Mod*> mods;
	Mod *currentlyUsing = nullptr;
};

inline Mod *ModHandler::getCurrentlyUsedMod()
{ 
	return currentlyUsing;
}