#ifndef RECT_H_
#define RECT_H_

#include "Rendering.h"
#include "math.h"

namespace Heavenly
{
    namespace Rendering
    {
        class Rect
        {
        public:
            Rect();

            inline RenderableComponent* GetRenderableComponent() { return renderable_comp; }

        private:
            std::vector<Vertex*> vertex_locations;
            RenderableComponent* renderable_comp { nullptr };
        };
    }
}

#endif //RECT_H_