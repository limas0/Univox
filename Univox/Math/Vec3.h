#pragma once
#include "..\API.h"

template<typename T>
struct Vec3
{
	Vec3();
	Vec3(T x, T y, T z);

	inline const bool operator==(const Vec3<T> &r) const noexcept;
	inline const Vec3<T> operator+(const Vec3<T> &r) const noexcept;
	inline const Vec3<T> operator-(const Vec3<T> &r) const noexcept;
	inline const Vec3<T> &operator+=(const Vec3<T> &r) noexcept;
	inline const Vec3<T> &operator-=(const Vec3<T> &r) noexcept;
	inline const Vec3<T> &operator*=(const Vec3<T> &r) noexcept;
	inline const Vec3<T> &operator/=(const Vec3<T> &r) noexcept;

	T x;
	T y;
	T z;
};

template<typename T>
Vec3<T>::Vec3() :
	x(0),
	y(0),
	z(0)
{

}

template<typename T>
Vec3<T>::Vec3(T x_, T y_, T z_) :
	x(x_),
	y(y_),
	z(z_)
{

}

template<typename T>
inline const bool Vec3<T>::operator==(const Vec3<T> &r) const noexcept
{
	return ((x == r.x) && (y == r.y) && (z == r.z));
}

template<typename T>
inline const Vec3<T> Vec3<T>::operator+(const Vec3<T> &r) const noexcept
{
	return Vec3<T>(x + r.x, y + r.y, z + r.z);
}

template<typename T>
inline const Vec3<T> Vec3<T>::operator-(const Vec3<T> &r) const noexcept
{
	return Vec3<T>(x - r.x, y - r.y, z - r.z);
}

template<typename T>
inline const Vec3<T> &Vec3<T>::operator+=(const Vec3<T>& r) noexcept
{
	x += r.x;
	y += r.y;
	z += r.z;
	return *this;
}

template<typename T>
inline const Vec3<T>& Vec3<T>::operator-=(const Vec3<T>& r) noexcept
{
	x -= r.x;
	y -= r.y;
	z -= r.z;
	return *this;
}

template<typename T>
inline const Vec3<T> &Vec3<T>::operator*=(const Vec3<T>& r) noexcept
{
	x *= r.x;
	y *= r.y;
	z *= r.z;
	return *this;
}

template<typename T>
inline const Vec3<T>& Vec3<T>::operator/=(const Vec3<T>& r) noexcept
{
	x /= r.x;
	y /= r.y;
	z /= r.z;
	return *this;
}
