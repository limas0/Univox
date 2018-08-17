#pragma once
#include "..\Header.h"
#include "..\Block\IBlock.h"

class UNIVOX_API BlockFactory
{
public:
	BlockFactory(IBlock *blockTemplate);
	~BlockFactory();

	void destroy();

	IBlock *createNew();

private:
	IBlock *m_blockTemplate = nullptr;
};

