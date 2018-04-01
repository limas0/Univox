#include "ModHandler.h"

ModHandler::ModHandler()
{

}

ModHandler::~ModHandler()
{

}

void ModHandler::destroy()
{
	for (auto mod : mods)
	{
		delete mod;
		mod = nullptr;
	}
	mods.clear();
}

void ModHandler::registerMod(Mod *mod)
{
	mods.push_back(mod);
}
