#include "WorldRenderer.h"
#include "WorldScene.h"

WorldRenderer::WorldRenderer()
{
}

WorldRenderer::~WorldRenderer()
{
}

void WorldRenderer::create(WorldScene *scene)
{
	p_scene = scene;
}

void WorldRenderer::destroy()
{

}

void WorldRenderer::setChunkMesh(ChunkMesh *mesh)
{
	p_scene->setChunkMesh(mesh);
}

inline ChunkMesh *WorldRenderer::getChunkMesh(Vec2i &index)
{
	p_scene->getChunkMesh(index);
}

void WorldRenderer::setWorld(World *world)
{
	p_scene->removeAllObjects();
	p_world = world;
}