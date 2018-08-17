#pragma once
#include "..\IO\Serializable.h"
#include "BlockModel.h"

class UNIVOX_API IBlock : public Serializable
{
public:
	virtual ~IBlock() = default;
	virtual IBlock *clone() const = 0;
	virtual inline size_t size() const = 0;

	virtual std::string getId() const = 0;
	virtual BlockModel &getBlockModel() const = 0;
};