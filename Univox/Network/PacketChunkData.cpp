#include "PacketChunkData.h"
#include "../Game.h"
#include "../World/Chunk/ChunkMeshBuilder.h"
#include <zlib.h>

PacketChunkData::PacketChunkData():
	Packet()
{
}

PacketChunkData::~PacketChunkData()
{
}

void PacketChunkData::pack()
{
	WE::Timer timer;
	timer.start();

	Packet::pack<PacketChunkData>();
	
	rawPacket << index.x << index.y;
	//std::string data = chunk.serialize();
	//rawPacket << data;

	std::vector<char> *data = toBytes(&chunk.blocks[0], Consts::CHUNK_VOLUME);

	z_stream s;
	memset(&s, 0, sizeof(s));

	if (deflateInit(&s, Z_DEFAULT_COMPRESSION))
		std::cout << "deflate init error" << std::endl;

	s.next_in = (Bytef*)data->data();//(Bytef*)data.data();
	s.avail_in = data->size();
	//std::cout << "total in: " << data.size() << std::endl;

	int ret;
	char outbuffer[32768];
	std::string outdata;

	do
	{
		s.next_out = reinterpret_cast<Bytef*>(outbuffer);
		s.avail_out = sizeof(outbuffer);

		ret = deflate(&s, Z_FINISH);

		std::cout << "total out: " << s.total_out << std::endl;
		outdata.append(outbuffer, s.total_out);
	} while (ret == Z_OK);

	deflateEnd(&s);

	if (ret != Z_STREAM_END) {
		std::cout << "error: " << s.msg << std::endl;
	}

	rawPacket << outdata;

	std::cout << "PacketChunkData packed in " << timer.stop() << "ms" << std::endl;

	delete data;
}

void PacketChunkData::unpack()
{
	WE::Timer timer;
	timer.start();

	rawPacket >> index.x >> index.y;
	std::string data;
	rawPacket >> data;
	
	std::cout << "inflate total in:" << data.size() << std::endl;

	z_stream s;
	memset(&s, 0, sizeof(s));

	if (inflateInit(&s, Z_DEFAULT_COMPRESSION))
		std::cout << "inflate init error" << std::endl;

	s.next_in = (Bytef*)data.data();
	s.avail_in = data.size();

	int ret;
	char outbuffer[135000];
	std::string outdata;

	do
	{
		s.next_out = reinterpret_cast<Bytef*>(outbuffer);
		s.avail_out = sizeof(outbuffer);

		ret = inflate(&s, 0);

		//std::cout << "inflate total out: " << s.total_out << std::endl;
		outdata.append(outbuffer, s.total_out);
	} while (ret == Z_OK);

	inflateEnd(&s);

	if (ret != Z_STREAM_END) {
		std::cout << "error: " << s.msg << std::endl;
	}

	fromBytes(outdata.data(), outdata.size(), &chunk.blocks[0]);
	//chunk.deserialize(outdata);

	std::cout << "PacketChunkData unpacked in " << timer.stop() << "ms" << std::endl;
}

bool PacketChunkData::dispatchServer(Server *server, sf::Packet *packet)
{
	PacketChunkData pake;
	pake.rawPacket = *packet;
	pake.unpack();

	std::cout << pake.index.x << pake.index.y << std::endl;

	return true;
}

bool PacketChunkData::dispatchClient(Client *client, sf::Packet *packet)
{
	PacketChunkData pake;
	pake.rawPacket = *packet;
	pake.unpack();

	std::cout << pake.index.x << pake.index.y << std::endl;

	auto chunk = client->getGame()->getWorld().getChunk(pake.index);

	chunk->setChunkData(pake.chunk);

	ChunkMesh *chunkMesh = new ChunkMesh();
	ChunkMeshBuilder(chunk, chunkMesh).build();
	chunkMesh->create();

	chunkMesh->setMaterial("Default");
	chunkMesh->setTranslation({ float(pake.index.x * Consts::CHUNK_SIZE), 0.f, float(pake.index.y * Consts::CHUNK_SIZE) });

	client->getGame()->getWorldRenderer().setChunkMesh(pake.index, chunkMesh);

	return true;
}
