#include "WorldRenderer.h"

WorldRenderer::WorldRenderer()
{
}

WorldRenderer::~WorldRenderer()
{
}

void WorldRenderer::create(Scene *scene)
{
	p_scene = scene;
}

void WorldRenderer::destroy()
{

}

void WorldRenderer::setChunkMesh(Vec2i &index, ChunkMesh *mesh)
{
	if (auto[exists, iter] = getChunkMeshIter(index); exists)
	{
		p_scene->removeObject(iter->second);
		meshes.erase(iter);
	}

	if (mesh)
	{
		p_scene->addObject(mesh);
		meshes[index] = mesh;
	}
}

inline ChunkMesh *WorldRenderer::getChunkMesh(Vec2i &index)
{
	MeshMap::iterator result = meshes.find(index);
	return result != meshes.end() ? result->second : nullptr;
}

inline std::tuple<bool, WorldRenderer::MeshMap::const_iterator> WorldRenderer::getChunkMeshIter(Vec2i &index)
{
	MeshMap::iterator result = meshes.find(index);
	return { result != meshes.end(), result };
}

void WorldRenderer::setWorld(World *world)
{
	p_scene->removeAllObjects();
	p_world = world;
}