#pragma once

#include "math/MathBaseTypes.h"

namespace Heavenly::Rendering
{

struct Vertex
{
	Vertex() = default;
	Vertex(
		const Math::Vector3<float> pos,
		const Math::Vector4<float> col = {255.f, 255.f, 255.f, 255.f},
		const Math::Vector2<float> uv = {0.f, 0.f}
	)
	: position(pos)
	, color(col)
	, uv(uv) {}

    Math::Vector3<float> position {0, 0, 0};
    Math::Vector4<float> color {255, 255, 255, 255};
    Math::Vector2<float> uv {0, 0};
};

struct Triangle
{
	Triangle() = default;
	Vertex verts[3];
};

struct Quad
{
	Quad() = default;
	Vertex verts[4];
};

} // Heavenly::Rendering