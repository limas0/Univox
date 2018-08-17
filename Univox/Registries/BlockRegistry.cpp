#include "BlockRegistry.h"

BlockRegistry::BlockRegistry()
{
}

BlockRegistry::~BlockRegistry()
{
	destroy();
}

void BlockRegistry::create(ModHandler *modHandler)
{
	p_modHandler = modHandler;
}

void BlockRegistry::destroy()
{
	for (auto iter = registry.begin(); iter != registry.end(); ++iter)
	{
		iter->second.destroy();
	}

	registry.clear();
}
