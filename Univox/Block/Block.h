#pragma once
#include <type_traits>
#include "BlockProperties.h"
#include "IBlock.h"
#include "..\Utils\Metadata.h"

template<typename T>
class Block : public IBlock
{
public:
	Block() = default;
	virtual ~Block() = default;

	virtual Block *clone() const;
	virtual inline size_t size() const;

	void serialize(ByteBuffer &outData) const;
	bool deserialize(ByteBuffer &inData);

	Metadata metadata;
};

template<typename T>
inline Block<T> *Block<T>::clone() const
{
	return new Block<T>(*this);
}

template<typename T>
inline size_t Block<T>::size() const
{
	return sizeof(*this);
}

template<typename T>
inline void Block<T>::serialize(ByteBuffer &outData) const
{
	outData << T::id;
	metadata.serialize(outData);
}

template<typename T>
inline bool Block<T>::deserialize(ByteBuffer &inData)
{
	int id;
	inData >> id;
	metadata.deserialize(inData);
	return true;
}
