#include "Rect.h"

using namespace Heavenly::Rendering;

Rect::Rect()
{
    renderable_comp = new RenderableComponent();
    vertex_locations[0].position = { -0.5f, 0.5f, .0f };
    vertex_locations[1].position = { -0.5f, -0.5f, .0f };
    vertex_locations[2].position = { 0.5f, 0.5f, .0f };

    VertexDataDescriptor position_data_desc;
    position_data_desc.data_offset = 0;
    position_data_desc.data_size = 3;
    position_data_desc.data_type = GL_FLOAT;
    position_data_desc.elements = 4;

    VertexDataDescriptor color_data_desc;

    data_descriptors.push_back(position_data_desc);

    // TODO: If this works, this is ugly.
    std::size_t data_size = position_data_desc.data_size * sizeof(float) * 3;

    renderable_comp->SetVBOData(vertex_locations.data(), data_size, data_descriptors);
}

void Rect::SetShader(int shader_program_id)
{
    renderable_comp->shader_program_id = shader_program_id;
}