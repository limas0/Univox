#include "BlockFactory.h"

BlockFactory::BlockFactory(IBlock *blockTemplate)
{
	m_blockTemplate = blockTemplate;
}

BlockFactory::~BlockFactory()
{
	
}

void BlockFactory::destroy()
{
	if (m_blockTemplate)
		delete m_blockTemplate;
	m_blockTemplate = nullptr;
}

IBlock *BlockFactory::createNew()
{
	return m_blockTemplate->clone();
}