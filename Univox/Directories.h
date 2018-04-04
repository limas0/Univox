#pragma once
#include "Header.h"

namespace filesystem = std::experimental::filesystem;
typedef filesystem::path FilePath;

namespace Dir
{

static FilePath Bin = "..\\bin";
static FilePath Mods = "mods";

}