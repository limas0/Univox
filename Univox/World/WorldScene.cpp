#include "WorldScene.h"
#include "Chunk\ChunkMesh.h"

WorldScene::WorldScene()
{
}

WorldScene::~WorldScene()
{
}

void WorldScene::update()
{
	{
		std::lock_guard<std::mutex> lockRemove(*toRemove.getMutex());

		for (auto meshToRemove : toRemove.getDeque())
		{
			Scene::removeObject(meshToRemove);
			if (auto[exists, iter] = getChunkMeshIter(meshToRemove->getIndex()); exists)
			{
				meshes.erase(iter);
			}
		}
		toRemove.getDeque().clear();
	}
	{
		std::lock_guard<std::mutex> lockAdd(*toAdd.getMutex());

		for (auto meshToAdd : toAdd.getDeque())
		{
			if (meshToAdd)
			{
				if (auto[exists, iter] = getChunkMeshIter(meshToAdd->getIndex()); exists)
				{
					Scene::removeObject(iter->second);
					meshes.erase(iter);
				}

				Scene::addObject(meshToAdd);
				meshes.emplace(meshToAdd->getIndex(), meshToAdd);
			}
		}
		toAdd.getDeque().clear();

	}
	Scene::update();
}

void WorldScene::setChunkMesh(ChunkMesh *mesh)
{
	if (mesh)
	{
		{//additional scope to prevent same mutex overlapping
			std::lock_guard<std::mutex> lockAdd(*toAdd.getMutex());

			for (auto it = toAdd.getDeque().begin(); it != toAdd.getDeque().end(); ++it)
			{
				if ((*it)->getIndex() == mesh->getIndex())//if present then replace
				{
					(*it)->destroy();
					delete *it;
					*it = mesh;
					return;//return to prevent push_back
				}
			}
		}

		toAdd.push_back(mesh);
	}
}

void WorldScene::removeChunkMesh(ChunkMesh *mesh)
{
	toRemove.push_back(mesh);
}

ChunkMesh *WorldScene::getChunkMesh(Vec2i &index)
{
	MeshMap::iterator result = meshes.find(index);
	return result != meshes.end() ? result->second : nullptr;
}

inline std::tuple<bool, MeshMap::const_iterator> WorldScene::getChunkMeshIter(const Vec2i &index)
{
	MeshMap::iterator result = meshes.find(index);
	return { result != meshes.end(), result };
}
