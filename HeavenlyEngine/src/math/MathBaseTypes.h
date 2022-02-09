#ifndef MATH_BASE_TYPES_H_
#define MATH_BASE_TYPES_H_

namespace Heavenly::Math
{

class Vector2
{
public:
	Vector2() = default;

	Vector2(float _x) : x(_x) {}
	Vector2(float _x, float _y) : x(_x), y(_y) {}

	float x = 0;
	float y = 0;
};

class Vector3
{
public:
	Vector3() = default;

	Vector3(float _x) : x(_x) {}
	Vector3(float _x, float _y) : x(_x), y(_y) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	float x = 0;
	float y = 0;
	float z = 0;
};

class Vector4
{
public:
	Vector4() = default;

	Vector4(float _x) : x(_x) {}
	Vector4(float _x, float _y) : x(_x), y(_y) {}
	Vector4(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;
};

}

#endif //MATH_BASE_TYPES_H_