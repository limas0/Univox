#pragma once
#include "Header.h"
#include "DirtBlock.h"

DLL_EXPORT void onLoad()
{
	std::cout << "test" << std::endl;
}

DLL_EXPORT void onInit(InitWrapper *wrapper)
{
	DirtBlockProperties::model.tex = { 0.f, 0.f, 1.f, 1.f };

	auto &blockRegistry = wrapper->getBlockRegistry();
	blockRegistry.registerBlock<DirtBlockProperties>(new DirtBlock());

	std::cout << "testInit" << std::endl;
}