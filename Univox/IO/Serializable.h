#pragma once
#include <string>

class Serializable
{
public:
	Serializable() = default;
	~Serializable() = default;

	virtual std::string serialize() const = 0;
	virtual bool deserialize(std::string data) const = 0;
};