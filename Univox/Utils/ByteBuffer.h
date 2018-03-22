#pragma once
#include <vector>
#include <zlib.h>

class ByteBuffer
{
public:
	ByteBuffer();
	ByteBuffer(const size_t size);
	~ByteBuffer();

	inline void resize(const size_t size);
	inline size_t getSizeInBytes();

	//dst could be resized in this function
	inline void compress(ByteBuffer &dst);

	//dst needs to have enough bytes allocated
	inline void decompress(ByteBuffer &dst);

	inline void toString(std::string &dst);
	inline void fromString(std::string &src);

	//do not delete manually
	inline char *getBytes();

	//count is the src container's element count
	template<typename T>
	inline void toBytes(const T *src);

	//dst needs to have at least buffer.size() bytes allocated 
	inline void fromBytes(void *dst);

	template<typename S = std::vector<char>, typename T>
	static inline S *toBytes(const T *src, const size_t count)
	{
		S *mid = new S();
		if constexpr(std::is_same_v<S, std::vector<char>>)
			mid->resize(count * sizeof(T));
		std::memcpy(&(*mid)[0], src, count * sizeof(T));
		return mid;
	}

	static inline void fromBytes(const char *src, const size_t count, void *dst)
	{
		std::memcpy(dst, src, count);
	}

	std::vector<char> buffer;
private:
	size_t sizeInBytes = 0;
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

inline size_t ByteBuffer::getSizeInBytes()
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
	s.avail_in = getSizeInBytes();

	int ret;

	do
	{
		s.next_out = reinterpret_cast<Bytef*>(dst.getBytes());
		s.avail_out = dst.getSizeInBytes();

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
	s.avail_in = getSizeInBytes();

	int ret;

	do
	{
		s.next_out = reinterpret_cast<Bytef*>(dst.getBytes());
		s.avail_out = dst.getSizeInBytes();

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
	dst.append(buffer.data(), buffer.size());
	dst.append('\0');
}

inline void ByteBuffer::fromString(std::string &src)
{
	resize(src.size());
	std::memcpy(&buffer[0], &src.data()[0], src.size());
}

inline char *ByteBuffer::getBytes()
{
	return buffer.data();
}

inline void ByteBuffer::fromBytes(void *dst)
{
	std::memcpy(dst, &buffer[0], buffer.size());
}

template<typename T>
inline void ByteBuffer::toBytes(const T *src)
{
	if (buffer.size() != sizeInBytes)
		buffer.resize(sizeInBytes);
	std::memcpy(&buffer[0], src, sizeInBytes);
}
