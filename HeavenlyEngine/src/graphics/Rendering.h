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
        struct Vertex
        {
            Math::Vector3 position      {0, 0, 0};
            Math::Vector4 color         {255, 255, 255, 255};
            Math::Vector2 uv            {0, 0};
        };

        struct VertexDataDescriptor
        {
            std::size_t data_size { 0 };
            std::size_t data_offset { 0 };
            std::size_t elements { 0 };
        };

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
            RenderableComponent();

            void SetVBOData(void* data, std::vector<VertexDataDescriptor> data_descriptors);

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

            //Creates rect at the center of the screen
            void CreateRect();

        private:
            RenderContext* render_context { nullptr };
            std::vector<RenderableComponent*> renderable_components;
        };
    }
}

#endif //OPEN_GL_RENDERER_H_