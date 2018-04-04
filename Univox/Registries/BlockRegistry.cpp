#include "BlockRegistry.h"

BlockRegistry::BlockRegistry()
{
}

BlockRegistry::~BlockRegistry()
{
	for (auto [key, val] : registry)
	{
		if (val)
			delete val;
		val = nullptr;
	}
}

void BlockRegistry::create(ModHandler *modHandler)
{
	p_modHandler = modHandler;
}

void BlockRegistry::destroy()
{
}
