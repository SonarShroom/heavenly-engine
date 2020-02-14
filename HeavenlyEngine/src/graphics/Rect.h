#ifndef RECT_H_
#define RECT_H_

#include "math.h"

namespace Heavenly
{
    namespace Rendering
    {
        class Rect : public RenderableComponent
        {
            Math::Vector3 vertexLocations[4];
        }
    }
}

#endif //RECT_H_