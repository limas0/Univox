#pragma once
#include "Header.h"
#include "DirtBlockProperties.h"

class DirtBlock : public Block<DirtBlockProperties>
{
	virtual DirtBlock *clone() const;
	virtual inline size_t size() const;
};

inline DirtBlock *DirtBlock::clone() const
{
	return new DirtBlock(*this);
}

inline size_t DirtBlock::size() const
{
	return sizeof(*this);
}