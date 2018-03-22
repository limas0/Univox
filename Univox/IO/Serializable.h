#pragma once
#include <string>

class Serializable
{
public:
	Serializable() = default;
	~Serializable() = default;

	virtual void serialize(ByteBuffer &) const = 0;
	virtual bool deserialize(ByteBuffer &) = 0;
};