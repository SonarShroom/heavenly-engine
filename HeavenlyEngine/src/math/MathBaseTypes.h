#pragma once

// #include <concepts>

// namespace Heavenly::Math
// {

// struct Vector2
// {
// public:
// 	Vector2(const float x = 0, const float y = 0) : data {x, y} { }

// 	operator float* () {
// 		return data.vec;
// 	}

// 	union {
// 		struct Data {
// 			float x;
// 			float y;
// 		};
// 		float vec[2] = {0, 0};
// 	} data;
// };	

// struct Vector3
// {
// public:
// 	Vector3(const float x = 0, const float y = 0, const float z = 0) : data {x, y, z} {}

// 	Vector3(const Vector2 vec2, const float z = 0) : Vector3(vec2.x, vec2.y, z) {}

// 	operator float* () {
// 		return data.vec;
// 	}

// 	union {
// 		struct Data {
// 			float x;
// 			float y;
// 			float z;
// 		};
// 		float vec[3] = {0, 0, 0};
// 	} data;
// };

// struct Vector4
// {
// public:
// 	Vector4(const float x = 0, const float y = 0, const float z = 0, const float w = 0) : data{x, y, z, w} {}

// 	Vector4(const Vector2 vec2, const float z = 0, const float w = 0) : Vector4(vec2.data.x, vec2.data.y, _z, _w) {}
// 	Vector4(const Vector3 vec3, const float w = 0) : Vector4(vec3.data.x, vec3.data.y, vec3.data.z, _w) {}

// 	operator float* () {
// 		return data.vec;
// 	}

// 	union {
// 		struct Data {
// 			float x;
// 			float y;
// 			float z;
// 			float w;
// 		} components;
// 		float vec[4] = {0, 0, 0, 0};
// 	} data;
// };

// }
