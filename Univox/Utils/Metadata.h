#pragma once
#include <string>
#include <string_view>
#include <map>

#include "..\IO\Serializable.h"
#include "ByteBuffer.h"

//Stores up to 255 properties
class UNIVOX_API Metadata : public Serializable
{
public:
	Metadata();
	~Metadata();

	//Returns true if the property was not present before
	inline bool setProperty(std::string key, std::string val);

	//Returns empty string if the property does not exist
	inline std::string_view getProperty(std::string key);

	virtual void serialize(ByteBuffer &dst) const;
	virtual bool deserialize(ByteBuffer &src);
private:
	std::map<std::string, std::string> data;
};

inline bool Metadata::setProperty(std::string key, std::string val)
{
	auto[iter, result] = data.insert_or_assign(key, val);
	return result;
}

inline std::string_view Metadata::getProperty(std::string key)
{
	if (data.find(key) != data.end())
	{
		return data.at(key);
	}
	return "";
}