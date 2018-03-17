#pragma once
#include "..\Header.h"
#include "Chunk\ChunkMesh.h"

class World;

class WorldRenderer
{
public:
	using MeshMap = std::unordered_map<Vec2i, ChunkMesh*>;

	WorldRenderer();
	~WorldRenderer();

	void create(Scene *scene);
	void destroy();

	void setChunkMesh(Vec2i &index, ChunkMesh *mesh);
	inline ChunkMesh *getChunkMesh(Vec2i &index);

	std::tuple<bool, WorldRenderer::MeshMap::const_iterator> getChunkMeshIter(Vec2i & index);

	void setWorld(World *world);
	inline Scene *getScene() const;

private:
	Scene *p_scene = nullptr;
	World *p_world = nullptr;
	MeshMap meshes;
};

inline Scene *WorldRenderer::getScene() const
{
	return p_scene;
}