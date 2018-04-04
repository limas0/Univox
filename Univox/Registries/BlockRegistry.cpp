#include "BlockRegistry.h"

BlockRegistry::BlockRegistry()
{
}

BlockRegistry::~BlockRegistry()
{
	for(auto iter = registry.begin(); iter != registry.end(); ++iter)
	{
		if (iter->second)
			delete iter->second;
		iter->second = nullptr;
	}
}

void BlockRegistry::create(ModHandler *modHandler)
{
	p_modHandler = modHandler;
}

void BlockRegistry::destroy()
{
}
