#pragma once

#include "math/MathBaseTypes.h"

namespace Heavenly::Graphics
{

struct Vertex
{
    Math::Vector3 position;
    Math::Vector4 color {255.f, 255.f, 255.f, 255.f};
    Math::Vector2 uv;
};

struct Triangle
{
	Vertex verts[3];
};

struct Quad
{
	Vertex verts[4];
};

} // Heavenly::Rendering