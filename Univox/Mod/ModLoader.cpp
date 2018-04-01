#include "ModLoader.h"
#include "ModHandler.h"

ModLoader::ModLoader()
{
}

ModLoader::~ModLoader()
{
}

void ModLoader::load(ModHandler *p_handler)
{
	auto availableMods = getAvailableMods();

	std::cout << "Available mods:" << std::endl;
	for (auto mod : availableMods)
	{
		if (mod.ableToLoad)
		{
			std::cout << '\t' << mod.modName << std::endl;

			Mod *newMod = new Mod(mod.modName);
			newMod->load(mod.path.string() + "mod.dll");

			p_handler->registerMod(newMod);
		}
		else
		{
			std::cout << '\t' << mod.modName << " - unable to load" << std::endl;
		}
	}
}

std::list<ModEntry> ModLoader::getAvailableMods()
{
	std::list<ModEntry> result;

	auto dir = Dir::Mods;
	if (IsDebuggerPresent())
		dir = Dir::Bin / dir;

	auto directoryEntries = FileHandler::getDirectoryEntries(dir);
	for (auto const entry : directoryEntries)
	{
		if (FileHandler::isDirectory(entry))
		{
			ModEntry newEntry;
			newEntry.modName = FileHandler::getFileName(entry).string();
			newEntry.ableToLoad = hasRequiredFiles(entry);
			newEntry.path = entry;

			result.push_back(newEntry);
		}
	}

	return result;
}

bool ModLoader::hasRequiredFiles(FilePath mod)
{
	auto tempRequiredFiles = requiredFiles;

	auto entries = FileHandler::getDirectoryEntries(mod);
	for (auto const entry : entries)
	{
		auto fileName = FileHandler::getFileName(entry, false);

		for (auto iter = tempRequiredFiles.begin(); iter != tempRequiredFiles.end(); ++iter)
		{
			if (fileName == *iter)
			{
				tempRequiredFiles.erase(iter);
				break;
			}
		}
	}

	return tempRequiredFiles.size() == 0;
}
