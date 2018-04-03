#include <iostream>

#pragma once
#define DLL_EXPORT extern "C" __declspec(dllexport)

DLL_EXPORT void onLoad()
{
	std::cout << "test" << std::endl;
}

DLL_EXPORT void onInit()
{
	std::cout << "testInit" << std::endl;
}