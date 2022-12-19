#pragma once

#include "RenderPrimitives.h"

namespace Heavenly::Graphics
{

struct RenderCommand
{
	enum class Type
	{
		DRAW_QUAD = 0,
		DRAW_TRIANGLE,
		USE_SHADER,
		SIZE
	} type;
	union Payload {
		Triangle triangle;
		Quad quad;
		unsigned int shaderProgramID;
	} payload;
};

} // Heavenly::Rendering