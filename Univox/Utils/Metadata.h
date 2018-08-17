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

	virtual inline void serialize(ByteBuffer &dst) const;
	virtual inline bool deserialize(ByteBuffer &src);
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

inline void Metadata::serialize(ByteBuffer &dst) const
{
	dst << std::uint8_t(data.size());
	for (auto iter = data.begin(); iter != data.end(); ++iter)
	{
		dst << iter->first << iter->second;
	}
}

inline bool Metadata::deserialize(ByteBuffer &src)
{
	std::uint8_t size = 0;
	src >> size;

	for (int i = 0; i < size; i++)
	{
		std::string key, val;
		src >> key >> val;
		setProperty(key, val);
	}

	return false;
}