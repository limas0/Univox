#pragma once

namespace Consts
{

static constexpr unsigned int CHUNK_SIZE = 16;
static constexpr unsigned int CHUNK_HEIGHT = 256;
static constexpr unsigned int CHUNK_WALL_AREA = CHUNK_SIZE * CHUNK_HEIGHT;
static constexpr unsigned int CHUNK_VOLUME = CHUNK_WALL_AREA * CHUNK_SIZE;

}