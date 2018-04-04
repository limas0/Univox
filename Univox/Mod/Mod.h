#pragma once
#include "..\Header.h"

class InitWrapper;

class UNIVOX_API Mod
{
public:
	Mod(std::string name);
	~Mod();

	void load(FilePath path);

	std::function<void()> onLoad;
	std::function<void(InitWrapper*)> onInit;

	std::string getName();

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
