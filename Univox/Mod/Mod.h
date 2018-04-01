#pragma once
#include "../Header.h"

class Mod
{
public:
	Mod(std::string name);
	~Mod();

	void load(std::string name);

private:
	template<typename T>
	inline std::function<T> getFunction(LPCSTR name) const;

	HMODULE handle = nullptr;
	std::string m_name = "";
};

template<typename T>
inline std::function<T> Mod::getFunction(LPCSTR name) const
{
	return std::function<T>(reinterpret_cast<T*>(GetProcAddress(handle, name)));

}
