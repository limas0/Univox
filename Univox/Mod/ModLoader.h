#pragma once
#include "../Header.h"

class ModHandler;

struct ModEntry
{
	std::string modName = "";
	bool ableToLoad = false;
	FilePath path;
};

class ModLoader
{
public:
	ModLoader();
	~ModLoader();

	void load(ModHandler *p_handler);

private:
	std::list<ModEntry> getAvailableMods();
	bool hasRequiredFiles(FilePath mod);

	std::list<std::string> requiredFiles =
	{
		"mod.dll",
		"modinfo"
	};
};

