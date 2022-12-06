#pragma once

#include <concepts>

namespace Heavenly::Math
{

struct Vector2 
{
public:
	Vector2(const float _x = 0, const float _y = 0) : x(_x), y(_y) {}

	float x = 0;
	float y = 0;
};	

struct Vector3
{
public:
	Vector3(const float _x = 0, const float _y = 0, const float _z = 0) : x(_x), y(_y), z(_z) {}

	Vector3(const Vector2 _vec2, const float _z = 0) : Vector3(_vec2.x, _vec2.y, _z) {}

	float x = 0;
	float y = 0;
	float z = 0;
};

struct Vector4
{
public:
	Vector4(const float _x = 0, const float _y = 0, const float _z = 0, const float _w = 0) : x(_x), y(_y), z(_z), w(_w) {}

	Vector4(const Vector2 _vec2, const float _z = 0, const float _w = 0) : Vector4(_vec2.x, _vec2.y, _z, _w) {}
	Vector4(const Vector3 _vec3, const float _w = 0) : Vector4(_vec3.x, _vec3.y, _vec3.z, _w) {}

	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;
};

}
