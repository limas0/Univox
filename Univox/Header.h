#pragma once
#include <Window.h>
#include <Message.h>
#include <Engine.h>
#include <RenderStates.h>
#include <Shader.h>
#include <FirstPersonCamera.h>
#include <Scene.h>
#include <Cube.h>
#include <Viewport.h>
#include <RenderStatistics.h>
#include <Mesh.h>
#include <PrimitiveBuilder.h>
#include <Sampler.h>
#include <VertexBufferIndexed.h>
#include <Timer.h>

#include "Math\Math.h"
#include "World\WorldConstants.h"
#include "Utils\ByteBuffer.h"

#define GAME Game::game

using WE::Mesh;
using WE::Scene;

class ChunkMesh;
using MeshMap = std::unordered_map<Vec2i, ChunkMesh*>;

//#ifdef UNIVOX_EXPORT_API
//#define UNIVOX_API __declspec(dllexport)
//#else
//#define UNIVOX_API __declspec(dllimport)
//#endif

#ifdef _MSC_VER
#pragma warning(disable: 4251)
#endif

namespace std {

template<>
struct hash<Vec2i>
{
	const int operator()(const Vec2i &index) const noexcept
	{
		std::hash<int> hasher;
		return int(hasher(index.x) ^ hasher(index.y));
		//std::hash<decltype(index.x)> hasher;
		//const int valuex = int(hasher(index.x));
		//const int valuey = int(hasher(index.y));
		//return int(std::hash<decltype(index.x)>{}((valuex ^ valuey) >> 2));
	}
};

}