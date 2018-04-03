#pragma once
#include "../../IO/Serializable.h"

class IBlock : public Serializable
{
public:
	virtual ~IBlock() = default;
	virtual IBlock *clone() const = 0;
	virtual inline size_t size() const = 0;
};