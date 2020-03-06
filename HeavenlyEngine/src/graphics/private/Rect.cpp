#include "Rect.h"

using namespace Heavenly::Rendering;

Rect::Rect()
{
    renderable_comp = new RenderableComponent();
    for(int currVertex = 0; currVertex < 4; currVertex++)
    {
        vertex_locations.push_back(new Vertex());
    }
    vertex_locations[0]->position = { -0.5f, 0.5f, -0.5f };
    vertex_locations[1]->position = { -0.5f, -0.5f, -0.5f };
    vertex_locations[2]->position = { 0.5f, -0.5f, -0.5f };
    vertex_locations[3]->position = { 0.5f, 0.5f, -0.5f };
    renderable_comp->SetVBOData(vertex_locations.data());
}

