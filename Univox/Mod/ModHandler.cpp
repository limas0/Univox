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

void ModHandler::loadAll()
{
	for (auto mod : mods)
	{
		currentlyUsing = mod;
		mod->onLoad();
		currentlyUsing = nullptr;
	}
}

void ModHandler::initAll(InitWrapper *wrapper)
{
	for (auto mod : mods)
	{
		currentlyUsing = mod;
		mod->onInit(wrapper);
		currentlyUsing = nullptr;
	}
}
