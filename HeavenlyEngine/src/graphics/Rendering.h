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
        class RenderContext : public EntityComponentSystem::Component
        {
        public:
            Math::Vector2 window_resolution {1280, 720};
            bool window_resizable {false};
            GLFWwindow* window {nullptr};
        };

        class RenderableComponent
        {
        public:
            RenderableComponent(unsigned int vbo_id, unsigned int vs_id, unsigned int fs_id, unsigned int sp_id) :
                vertex_buffer_object_id(vbo_id),
                vertex_shader_id(vs_id),
                fragment_shader_id(fs_id),
                shader_program_id(sp_id) {};

            unsigned int vertex_buffer_object_id    { 0 };
            unsigned int vertex_shader_id           { 0 };
            unsigned int fragment_shader_id         { 0 };
            unsigned int shader_program_id          { 0 };
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