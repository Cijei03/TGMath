#pragma once
#include "../TGBasicTypes.hpp"

namespace TGMath
{
	constexpr TGf32 PI = 3.141592;

	template<typename T>
	T convertDigreesToRadians(const T degrees)
	{
		return degrees * (PI / 180.0f);
	}
	template<typename T>
	T convertRadiansToDigrees(const T radians)
	{
		return radians * (180.0f / PI);
	}
	template<typename T>
	T sqr(const T value)
	{
		return T(value * value);
	}
	template<typename T>
	T pow(const T value, TGui32 power)
	{
		T cache = value;
		for (TGui32 i = 0; i < power; i++)
		{
			cache = cache * cache;
		}
		return cache;
	}
	template<typename T>
	T clip(const T min, const T max, T value)
	{
		if (value < min) return min;
		else if (value > max) return max;
		return value;
	}
}