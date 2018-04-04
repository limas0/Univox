#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <functional>
#include <string>
#include <array>
#include <math.h>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <istream>
#include <sstream>
#include <map>
#include <thread>
#include <mutex>
#include <iomanip>
#include <memory>
#include <type_traits>
#include <atomic>
#include <deque>
#include <string_view>
#include <cctype>

#include "Math\Math.h"
#include "World\WorldConstants.h"
#include "Utils\ByteBuffer.h"
#include "Directories.h"

#include <winsock.h>
#include <Windows.h>

#define GAME Game::game

class ChunkMesh;
using MeshMap = std::unordered_map<Vec2i, ChunkMesh*>;

#ifndef NOT_UNIVOX_EXPORT_API
	#ifdef UNIVOX_EXPORT_API
		#define UNIVOX_API __declspec(dllexport)
	#else
		#define UNIVOX_API __declspec(dllimport)
	#endif
#else
	#define UNIVOX_API
#endif

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