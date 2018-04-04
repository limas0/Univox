#pragma once
#include "..\Header.h"
#include "..\EngineHeader.h"

template<typename T>
class SafeDeque
{
public:
	SafeDeque()
	{
		m = new std::mutex();
	}
	~SafeDeque()
	{
		delete m;
	}

	bool back(T &t)
	{
		bool result = false;
		m->lock();
		if (!deque.empty())
		{
			t = deque.back();
			result = true;
		}
		m->unlock();
		return result;
	}

	bool front(T &t)
	{
		bool result = false;
		m->lock();
		if (!deque.empty())
		{
			t = deque.front();
			result = true;
		}
		m->unlock();
		return result;
	}

	void pop_back()
	{
		m->lock();
		if (!deque.empty())
			deque.pop_back();
		m->unlock();
	}

	void pop_front()
	{
		m->lock();
		if (!deque.empty())
			deque.pop_front();
		m->unlock();
	}

	void push_back(const T t)
	{
		m->lock();
		deque.push_back(t);
		m->unlock();
	}

	void push_front(const T t)
	{
		m->lock();
		deque.push_front(t);
		m->unlock();
	}

	std::mutex *getMutex()
	{
		return m;
	}

	std::deque<T> &getDeque()
	{
		return deque;
	}

private:
	std::deque<T> deque;
	std::mutex *m = nullptr;
};

class ChunkMesh;

class WorldScene : public Scene
{
public:
	WorldScene();
	~WorldScene();

	void update();

	void setChunkMesh(ChunkMesh *mesh);
	void removeChunkMesh(ChunkMesh *mesh);

	ChunkMesh *getChunkMesh(Vec2i &index);
	std::tuple<bool, MeshMap::const_iterator> getChunkMeshIter(const Vec2i &index);
private:
	SafeDeque<ChunkMesh*> toAdd;
	SafeDeque<ChunkMesh*> toRemove;

	MeshMap meshes;
};