#pragma once

#include "RenderPrimitives.h"

namespace Heavenly::Rendering
{

struct RenderCommand
{
	enum class Type
	{
		DRAW_QUAD = 0,
		DRAW_TRIANGLE,
		SIZE
	};
	union Payload {
		Triangle triangle;
		Quad quad;
	} payload;

	Type type;
};

} // Heavenly::Rendering