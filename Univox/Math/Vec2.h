#pragma once

template<typename T>
struct Vec2
{
	Vec2();
	Vec2(T x, T y);

	inline const bool operator==(const Vec2<T> &r) const noexcept;
	inline const Vec2<T> operator+(const Vec2<T> &r) const noexcept;
	inline const Vec2<T> operator-(const Vec2<T> &r) const noexcept;
	inline const Vec2<T> &operator+=(const Vec2<T> &r) noexcept;
	inline const Vec2<T> &operator-=(const Vec2<T> &r) noexcept;
	inline const Vec2<T> &operator*=(const Vec2<T> &r) noexcept;
	inline const Vec2<T> &operator/=(const Vec2<T> &r) noexcept;
	
	T x;
	T y;
};

template<typename T>
Vec2<T>::Vec2() :
	x(0),
	y(0)
{

}

template<typename T>
Vec2<T>::Vec2(T x_, T y_):
	x(x_),
	y(y_)
{
	
}

template<typename T>
inline const bool Vec2<T>::operator==(const Vec2<T> &r) const noexcept
{
	return ((x == r.x) && (y == r.y));
}

template<typename T>
inline const Vec2<T> Vec2<T>::operator+(const Vec2<T> &r) const noexcept
{
	return Vec2<T>(x + r.x, y + r.y);
}

template<typename T>
inline const Vec2<T> Vec2<T>::operator-(const Vec2<T> &r) const noexcept
{
	return Vec2<T>(x - r.x, y - r.y);
}

template<typename T>
inline const Vec2<T> &Vec2<T>::operator+=(const Vec2<T>& r) noexcept
{
	x += r.x;
	y += r.y;
	return *this;
}

template<typename T>
inline const Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& r) noexcept
{
	x -= r.x;
	y -= r.y;
	return *this;
}

template<typename T>
inline const Vec2<T> &Vec2<T>::operator*=(const Vec2<T>& r) noexcept
{
	x *= r.x;
	y *= r.y;
	return *this;
}

template<typename T>
inline const Vec2<T>& Vec2<T>::operator/=(const Vec2<T>& r) noexcept
{
	x /= r.x;
	y /= r.y;
	return *this;
}
