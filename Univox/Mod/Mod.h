#pragma once
#include "../Header.h"

class Mod
{
public:
	Mod(std::string name);
	~Mod();

	void load(FilePath path);

	std::function<void()> onLoad;
	std::function<void()> onInit;

private:
	template<typename T>
	inline std::function<T> getFunction(LPCSTR name) const;

	HMODULE handle = nullptr;
	std::string m_name = "";
};

template<typename T>
inline std::function<T> Mod::getFunction(LPCSTR name) const
{
	auto procAddress = GetProcAddress(handle, name);
	if (!procAddress)
	{
		std::cout << "Cannot get function '" << name << "' error: " << GetLastError() << std::endl;
	}
	return std::function<T>(reinterpret_cast<T*>(procAddress));

}
