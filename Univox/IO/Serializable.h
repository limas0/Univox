#pragma once
#include <string>
#include "..\Utils\ByteBuffer.h"

class UNIVOX_API Serializable
{
public:
	Serializable() = default;
	~Serializable() = default;

	virtual void serialize(ByteBuffer &) const = 0;
	virtual bool deserialize(ByteBuffer &) = 0;
};