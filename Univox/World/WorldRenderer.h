#pragma once
#include "..\Header.h"
#include "..\EngineHeader.h"
#include "Chunk\ChunkMesh.h"

class World;
class WorldScene;

class WorldRenderer
{
public:
	WorldRenderer();
	~WorldRenderer();

	void create(WorldScene *scene);
	void destroy();

	void setChunkMesh(ChunkMesh *mesh);
	inline ChunkMesh *getChunkMesh(Vec2i &index);

	void setWorld(World *world);
	inline WorldScene *getScene() const;

private:
	WorldScene *p_scene = nullptr;
	World *p_world = nullptr;
};

inline WorldScene *WorldRenderer::getScene() const
{
	return p_scene;
}