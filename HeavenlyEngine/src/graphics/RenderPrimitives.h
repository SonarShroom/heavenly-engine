#pragma once

#include "HeavenlyMath.h"

namespace Heavenly::Graphics
{

struct Vertex
{
    glm::vec3 position = {0.f, 0.f, 0.f};
    glm::vec4 color = {255.f, 255.f, 255.f, 255.f};
    glm::vec2 uv = {0.f, 0.f};
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