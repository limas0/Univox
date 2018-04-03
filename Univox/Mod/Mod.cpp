#include "Mod.h"

Mod::Mod(std::string name):
	m_name(name)
{
}

Mod::~Mod()
{
	FreeLibrary(handle);
}

void Mod::load(FilePath path)
{
	handle = LoadLibrary(path.string().c_str());
	if (!handle)
	{
		std::cout << "Cannot load mod '" << m_name << "' error: " << GetLastError() << std::endl;
	}

	onLoad = getFunction<void()>("onLoad");
	onInit = getFunction<void()>("onInit");
}