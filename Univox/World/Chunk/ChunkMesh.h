#pragma once
#include "../../Header.h"

class ChunkMesh : public Mesh<WE::VertexBuffer<WE::SceneObject::Vertex>>
{
public:
	ChunkMesh();
	~ChunkMesh();

	void create();
	void destroy();

	void update();
	void draw();

private:

};