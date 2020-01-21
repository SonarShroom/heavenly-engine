#ifndef OPEN_GL_RENDERER_H_
#define OPEN_GL_RENDERER_H_

#include "EntityComponentSystem.h"
#include "MathBaseTypes.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Heavenly
{
    namespace Rendering
    {
        int InitializeOpenGLRenderer();

        class RenderContext : EntityComponentSystem::Component
        {
            GLFWwindow* window {nullptr};
        };

        class Renderer : EntityComponentSystem::System
        {
        public:
            int InitContext();
            void Tick(float time_delta) override;
        };
    }
}

#endif //OPEN_GL_RENDERER_H_