#ifndef OPEN_GL_RENDERER_H_
#define OPEN_GL_RENDERER_H_

#include "EntityComponentSystem.h"
#include "MathBaseTypes.h"

#include <GLFW/glfw3.h>

namespace Heavenly
{
    namespace Rendering
    {
        class GLFWContext : EntityComponentSystem::Component
        {
            GLFWwindow* window;
            int open_gl_error {0};
        };

        class OpenGLSystem : EntityComponentSystem::System
        {
            void Tick(float time_delta) override;
        };
    }
}

#endif //OPEN_GL_RENDERER_H_