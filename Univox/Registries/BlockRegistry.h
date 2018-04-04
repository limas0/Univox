#pragma once
#include "..\Header.h"
#include "..\Factory\BlockFactory.h"
#include "..\Mod\ModHandler.h"

class UNIVOX_API BlockRegistry
{
public:
	BlockRegistry();
	~BlockRegistry();

	void create(ModHandler *modHandler);
	void destroy();

	template<typename P>
	inline void registerBlock(IBlock *blockTemplate);

private:
	std::unordered_map<std::string, BlockFactory*> registry;

	ModHandler *p_modHandler = nullptr;
};

template<typename P>
inline void BlockRegistry::registerBlock(IBlock *blockTemplate)
{
	std::string id = p_modHandler->getCurrentlyUsedMod()->getName() + ":" + P::id;
	std::transform(id.begin(), id.end(), id.begin(), tolower);
	registry.emplace(std::make_pair(id, new BlockFactory(blockTemplate)));
	std::cout << "Registered block[" << "id: " << id << "]" << std::endl;
}
