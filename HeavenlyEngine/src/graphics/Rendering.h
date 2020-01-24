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

        class RenderContext : public EntityComponentSystem::Component
        {
        public:
            GLFWwindow* window {nullptr};
        };

        class RenderableComponent : public EntityComponentSystem::Component
        {

        };

        class Renderer
        {
        public:
            Renderer() = default;
            ~Renderer() = default;
            
            int InitContext();
            bool ShouldCloseWindow();

            void Tick(float time_delta);

        private:
            RenderContext* render_context { nullptr };
            std::vector<RenderableComponent*> renderable_components;
        };
    }
}

#endif //OPEN_GL_RENDERER_H_