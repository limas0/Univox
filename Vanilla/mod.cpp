#pragma once
#include "Header.h"
#include "DirtBlock.h"

DLL_EXPORT void onLoad()
{
	std::cout << "test" << std::endl;
}

DLL_EXPORT void onInit(InitWrapper *wrapper)
{
	auto &blockRegistry = wrapper->getBlockRegistry();
	blockRegistry.registerBlock<DirtBlockProperties>(new DirtBlock());

	std::cout << "testInit" << std::endl;
}