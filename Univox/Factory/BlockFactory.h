#pragma once
#include "..\Header.h"
#include "..\Block\IBlock.h"

class UNIVOX_API BlockFactory
{
public:
	BlockFactory(IBlock *blockTemplate);
	~BlockFactory();

	IBlock *createNew();

private:
	IBlock *m_blockTemplate = nullptr;
};

