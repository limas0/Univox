#pragma once
#include <string>

class Serializable
{
public:
	Serializable() = default;
	~Serializable() = default;

	//virtual void *serialize() const = 0;
	//virtual bool deserialize(void *data) = 0;
	virtual std::string serialize() const = 0;
	virtual bool deserialize(std::string &) = 0;
};