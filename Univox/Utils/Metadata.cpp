#include "Metadata.h"

Metadata::Metadata()
{

}

Metadata::~Metadata()
{

}

void Metadata::serialize(ByteBuffer &dst) const
{
	dst << std::uint8_t(data.size());
	for (auto iter = data.begin(); iter != data.end(); ++iter)
	{
		dst << iter->first << iter->second;
	}
}

bool Metadata::deserialize(ByteBuffer &src)
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
