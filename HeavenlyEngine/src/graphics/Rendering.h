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
            Math::Vector2 window_resolution {1280, 720};
            bool window_resizable {false};
            GLFWwindow* window {nullptr};
        };

        class RenderableComponent : public EntityComponentSystem::Component
        {

        };

        class Renderer
        {
        public:
            Renderer() = default;
            ~Renderer();

            int InitContext(int window_width = 1280, int window_height = 720, bool window_resizable = true);
            bool ShouldCloseWindow();

            void Tick(float time_delta);

        private:
            RenderContext* render_context { nullptr };
            std::vector<RenderableComponent*> renderable_components;
        };
    }
}

#endif //OPEN_GL_RENDERER_H_