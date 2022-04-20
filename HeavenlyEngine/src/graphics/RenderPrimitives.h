#pragma once

#include "math/MathBaseTypes.h"

namespace Heavenly::Rendering
{

struct Vertex
{
    Math::Vector3<float> position {0, 0, 0};
    Math::Vector4<float> color {255, 255, 255, 255};
    Math::Vector2<float> uv {0, 0};
};

struct Triangle
{
	Vertex vertex[3];
};

struct Quad
{
	Vertex vertex[4];
};

} // Heavenly::Rendering