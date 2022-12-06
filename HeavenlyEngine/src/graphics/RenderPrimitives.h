#pragma once

#include "math/MathBaseTypes.h"

namespace Heavenly::Rendering
{

struct Vertex
{
    Math::Vector3 position {0.f, 0.f, 0.f};
    Math::Vector4 color {255.f, 255.f, 255.f, 255.f};
    Math::Vector2 uv {0.f, 0.f};
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