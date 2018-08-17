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

	inline BlockFactory *get(std::string id);

private:
	std::unordered_map<std::string, BlockFactory> registry;

	ModHandler *p_modHandler = nullptr;
};

template<typename P>
inline void BlockRegistry::registerBlock(IBlock *blockTemplate)
{
	std::string id = p_modHandler->getCurrentlyUsedMod()->getName() + ":" + P::name;
	std::transform(id.begin(), id.end(), id.begin(), tolower);
	P::id = id;
	registry.emplace(std::make_pair(id, BlockFactory(blockTemplate)));
	std::cout << "Registered block[" << "id: " << id << "]" << std::endl;
}

inline BlockFactory *BlockRegistry::get(std::string id)
{
	if(registry.find(id) != registry.end())
		return &registry.at(id);
	return nullptr;
}
