#pragma once
#include "..\API.h"

template<typename T>
struct Vec4
{
	Vec4();
	Vec4(T x, T y, T z, T w);

	inline const bool operator==(const Vec4<T> &r) const noexcept;
	inline const Vec4<T> operator+(const Vec4<T> &r) const noexcept;
	inline const Vec4<T> operator-(const Vec4<T> &r) const noexcept;
	inline const Vec4<T> &operator+=(const Vec4<T> &r) noexcept;
	inline const Vec4<T> &operator-=(const Vec4<T> &r) noexcept;
	inline const Vec4<T> &operator*=(const Vec4<T> &r) noexcept;
	inline const Vec4<T> &operator/=(const Vec4<T> &r) noexcept;

	T x;
	T y;
	T z;
	T w;
};

template<typename T>
Vec4<T>::Vec4() :
	x(0),
	y(0),
	z(0),
	w(0)
{

}

template<typename T>
Vec4<T>::Vec4(T x_, T y_, T z_, T w_) :
	x(x_),
	y(y_),
	z(z_),
	w(w_)
{

}

template<typename T>
inline const bool Vec4<T>::operator==(const Vec4<T> &r) const noexcept
{
	return ((x == r.x) && (y == r.y) && (z == r.z) && (w == r.w));
}

template<typename T>
inline const Vec4<T> Vec4<T>::operator+(const Vec4<T> &r) const noexcept
{
	return Vec4<T>(x + r.x, y + r.y, z + r.z, w + r.w);
}

template<typename T>
inline const Vec4<T> Vec4<T>::operator-(const Vec4<T> &r) const noexcept
{
	return Vec4<T>(x - r.x, y - r.y, z - r.z, w - r.w);
}

template<typename T>
inline const Vec4<T> &Vec4<T>::operator+=(const Vec4<T>& r) noexcept
{
	x += r.x;
	y += r.y;
	z += r.z;
	w += r.w;
	return *this;
}

template<typename T>
inline const Vec4<T>& Vec4<T>::operator-=(const Vec4<T>& r) noexcept
{
	x -= r.x;
	y -= r.y;
	z -= r.z;
	w -= r.w;
	return *this;
}

template<typename T>
inline const Vec4<T> &Vec4<T>::operator*=(const Vec4<T>& r) noexcept
{
	x *= r.x;
	y *= r.y;
	z *= r.z;
	w *= r.w;
	return *this;
}

template<typename T>
inline const Vec4<T>& Vec4<T>::operator/=(const Vec4<T>& r) noexcept
{
	x /= r.x;
	y /= r.y;
	z /= r.z;
	w /= r.w;
	return *this;
}
