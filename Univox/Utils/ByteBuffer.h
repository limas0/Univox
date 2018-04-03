#pragma once
#include <vector>
#include <zlib.h>
#include <iostream>

class ByteBuffer
{
public:
	ByteBuffer();
	ByteBuffer(const size_t size);
	~ByteBuffer();

	inline void resize(const size_t size);
	inline size_t getSizeInBytes() const;

	//dst could be resized in this function
	inline void compress(ByteBuffer &dst);

	//dst needs to have enough bytes allocated
	inline void decompress(ByteBuffer &dst);

	inline void toString(std::string &dst);
	inline void fromString(std::string &src);

	//do not delete manually
	inline unsigned char *getBytes();

	//count is the src container's element count
	template<typename T>
	inline void toBytes(const T *src);

	//dst needs to have at least buffer.size() bytes allocated 
	inline void fromBytes(void *dst);

	template<typename S = std::vector<unsigned char>, typename T>
	static inline S *toBytes(const T *src, const size_t count)
	{
		S *mid = new S();
		if constexpr(std::is_same_v<S, std::vector<unsigned char>>)
			mid->resize(count * sizeof(T));
		std::memcpy(&(*mid)[0], src, count * sizeof(T));
		return mid;
	}

	static inline void fromBytes(const unsigned char *src, const size_t count, void *dst)
	{
		std::memcpy(dst, src, count);
	}

	void append(const void *data, size_t bytes);

	ByteBuffer &operator<<(const int &val);
	ByteBuffer &operator>>(int &val);

	ByteBuffer &operator<<(const size_t &val);
	ByteBuffer &operator>>(size_t &val);

	ByteBuffer &operator<<(const std::string &val);
	ByteBuffer &operator>>(std::string &val);

	ByteBuffer &operator<<(const ByteBuffer &val);
	ByteBuffer &operator>>(ByteBuffer &val);

	std::vector<unsigned char> buffer;
private:
	size_t sizeInBytes = 0;
	size_t readPos = 0;
};

inline ByteBuffer::ByteBuffer()
{
}

inline ByteBuffer::ByteBuffer(const size_t size)
{
	resize(size);
}

inline ByteBuffer::~ByteBuffer()
{
}

inline void ByteBuffer::resize(const size_t size)
{
	sizeInBytes = size;
	buffer.resize(size);
}

inline size_t ByteBuffer::getSizeInBytes() const
{
	return buffer.size();
}

inline void ByteBuffer::compress(ByteBuffer &dst)
{
	dst.resize(getSizeInBytes());

	z_stream s;
	memset(&s, 0, sizeof(s));

	if (deflateInit(&s, Z_DEFAULT_COMPRESSION))
		std::cout << "deflate init error" << std::endl;

	s.next_in = (Bytef*)getBytes();
	s.avail_in = uInt(getSizeInBytes());

	int ret;

	do
	{
		s.next_out = reinterpret_cast<Bytef*>(dst.getBytes());
		s.avail_out = uInt(dst.getSizeInBytes());

		ret = deflate(&s, Z_FINISH);

		dst.resize(s.total_out);
	} while (ret == Z_OK);

	deflateEnd(&s);

	if (ret != Z_STREAM_END) {
		std::cout << "error: " << s.msg << std::endl;
	}
}

inline void ByteBuffer::decompress(ByteBuffer &dst)
{
	z_stream s;
	memset(&s, 0, sizeof(s));

	if (inflateInit(&s))
		std::cout << "inflate init error" << std::endl;

	s.next_in = (Bytef*)getBytes();
	s.avail_in = uInt(getSizeInBytes());

	int ret;

	do
	{
		s.next_out = reinterpret_cast<Bytef*>(dst.getBytes());
		s.avail_out = uInt(dst.getSizeInBytes());

		ret = inflate(&s, 0);

		dst.resize(s.total_out);
	} while (ret == Z_OK);

	inflateEnd(&s);

	if (ret != Z_STREAM_END) {
		std::cout << "error: " << s.msg << std::endl;
	}
}

inline void ByteBuffer::toString(std::string &dst)
{
	dst.append((char*)buffer.data(), buffer.size());
	dst.append('\0');
}

inline void ByteBuffer::fromString(std::string &src)
{
	resize(src.size());
	std::memcpy(&buffer[0], &src.data()[0], src.size());
}

inline unsigned char *ByteBuffer::getBytes()
{
	return buffer.data();
}

inline void ByteBuffer::fromBytes(void *dst)
{
	std::memcpy(dst, &buffer[0], buffer.size());
}

inline void ByteBuffer::append(const void *data, size_t bytes)
{
	size_t location = buffer.size();
	buffer.resize(location + bytes);
	std::memcpy(&buffer[location], data, bytes);
}

inline ByteBuffer &ByteBuffer::operator<<(const int &val)
{
	append(&val, sizeof(int));
	return *this;
}

inline ByteBuffer &ByteBuffer::operator>>(int &val)
{
	std::memcpy(&val, &buffer[readPos], sizeof(int));
	readPos += sizeof(int);
	return *this;
}

inline ByteBuffer &ByteBuffer::operator<<(const size_t &val)
{
	append(&val, sizeof(size_t));
	return *this;
}

inline ByteBuffer &ByteBuffer::operator>>(size_t &val)
{
	std::memcpy(&val, &buffer[readPos], sizeof(size_t));
	readPos += sizeof(size_t);
	return *this;
}

inline ByteBuffer &ByteBuffer::operator<<(const std::string &val)
{
	size_t size = val.size();
	append(&size, sizeof(size_t));
	append(val.data(), size);
	return *this;
}

inline ByteBuffer &ByteBuffer::operator>>(std::string &val)
{
	size_t size = 0;
	operator>>(size);
	val.clear();
	val.resize(size);
	val.assign((char*)&buffer[readPos], size);
	readPos += size;
	return *this;
}

inline ByteBuffer &ByteBuffer::operator<<(const ByteBuffer &val)
{
	size_t size = val.getSizeInBytes();
	append(&size, sizeof(size_t));
	append(&val.buffer[0], size);
	return *this;
}

inline ByteBuffer &ByteBuffer::operator>>(ByteBuffer &val)
{
	size_t size = 0;
	operator>>(size);
	val.append(&buffer[readPos], size);
	readPos += size;
	return *this;
}

template<typename T>
inline void ByteBuffer::toBytes(const T *src)
{
	if (buffer.size() != sizeInBytes)
		buffer.resize(sizeInBytes);
	std::memcpy(&buffer[0], src, sizeInBytes);
}
