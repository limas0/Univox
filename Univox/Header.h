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

#define GAME Game::game

using WE::Mesh;
using WE::Scene;

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

template<typename S = std::vector<char>, typename T>
inline S *toBytes(const T *src, const size_t count)
{
	S *mid = new S();
	if constexpr(std::is_same_v<S, std::vector<char>>)
		mid->resize(count * sizeof(T));
	std::memcpy(&(*mid)[0], src, count * sizeof(T));
	return mid;
}

inline void fromBytes(const char *src, const size_t count, void *dst)
{
	std::memcpy(dst, src, count);
}