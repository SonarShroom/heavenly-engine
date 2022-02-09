#ifndef RECT_H_
#define RECT_H_

#include "Rendering.h"

#include <array>

namespace Heavenly::Rendering
{

class Rect
{
public:
	Rect();

	inline RenderableComponent* GetRenderableComponent() { return renderable_comp; }

	void SetShader(int shader_program_id);

private:
	std::array<Vertex, 3> vertex_locations;
	std::vector<VertexDataDescriptor> data_descriptors;
	RenderableComponent* renderable_comp { nullptr };
};

}

#endif //RECT_H_
