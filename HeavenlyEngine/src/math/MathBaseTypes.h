#pragma once

#include <concepts>

namespace Heavenly::Math
{

template <typename NumberT>
requires std::integral<NumberT> || std::floating_point<NumberT>
struct Vector2 
{
public:
	Vector2() = default;

	Vector2(const NumberT _x) : x(_x) {}
	Vector2(const NumberT _x, const NumberT _y) : x(_x), y(_y) {}

	NumberT x = 0;
	NumberT y = 0;
};	

template <typename NumberT>
requires std::integral<NumberT> || std::floating_point<NumberT>
struct Vector3
{
public:
	Vector3() = default;

	Vector3(const NumberT _x) : x(_x) {}
	Vector3(const NumberT _x, const NumberT _y) : x(_x), y(_y) {}
	Vector3(const NumberT _x, const NumberT _y, const NumberT _z) : x(_x), y(_y), z(_z) {}

	NumberT x = 0;
	NumberT y = 0;
	NumberT z = 0;
};

template <typename NumberT>
requires std::integral<NumberT> || std::floating_point<NumberT>
struct Vector4
{
public:
	Vector4() = default;

	Vector4(const NumberT _x) : x(_x) {}
	Vector4(const NumberT _x, const NumberT _y) : x(_x), y(_y) {}
	Vector4(const NumberT _x, const NumberT _y, const NumberT _z) : x(_x), y(_y), z(_z) {}
	Vector4(const NumberT _x, const NumberT _y, const NumberT _z, const NumberT _w) : x(_x), y(_y), z(_z), w(_w) {}

	NumberT x = 0;
	NumberT y = 0;
	NumberT z = 0;
	NumberT w = 0;
};

}
