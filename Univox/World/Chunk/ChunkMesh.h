#pragma once
#include "..\..\Header.h"
#include "..\..\EngineHeader.h"

class ChunkMesh : public Mesh<WE::VertexBuffer<WE::SceneObject::Vertex>>
{
public:
	ChunkMesh();
	~ChunkMesh();

	void create(Vec2i index);
	void destroy();

	void update();
	void draw();

	inline const Vec2i &getIndex() const;
private:
	Vec2i m_index;
};

inline const Vec2i &ChunkMesh::getIndex() const
{
	return m_index;
}