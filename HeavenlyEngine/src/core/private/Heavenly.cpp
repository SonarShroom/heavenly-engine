#include "HeavenlyVersion.h"
#include "Heavenly.h"
#include "EntityComponentSystem.h"
#include "Rendering.h"
#include "LogManager.h"

#include <iostream>
#include <chrono>

#include "imgui.h"

void Heavenly::InitializeEngine()
{
    // TODO: When more engine subsystems should be initialized, add them here.
    Logging::LogManager::Init();

    // TODO: This file should be manually configured by cmake in order to hold version info here.
    HV_LOG_INFO("Engine", "Heavenly Started. Version: {}", HEAVENLY_VERSION);
}

int Heavenly::Run(int argc, char** argv)
{
    InitializeEngine();

    HV_LOG_INFO("Engine", "Heavenly Engine Started");

    HV_LOG_INFO("Engine", "Creating Subsystems...");

    HV_LOG_INFO("Engine", "Creating EntityAdmin...");

    auto admin = new EntityComponentSystem::WorldAdmin();

    HV_LOG_INFO("Engine","Creating Renderer...");

    auto renderer = new Rendering::Renderer();
    renderer->InitContext(600, 400, false);

    // TODO: This is not a good API to be honest... must rework asap after getting the rect on screen.
    const char* vertex_shader_source = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    int vertex_shader_id = 0;
    bool vert_success = renderer->RegisterNewVertexShader(vertex_shader_source, vertex_shader_id);

    const char* frag_shader_source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";
    int frag_shader_id = 0;
    bool frag_success = renderer->RegisterNewFragmentShader(frag_shader_source, frag_shader_id);

    if (!vert_success || !frag_success)
    {
        HV_LOG_ERROR("Engine", "Creating rect without shader program...");
        renderer->CreateRect();
    }
    else
    {
        int shader_program_id = 0;
        bool link_success = renderer->RegisterNewShaderProgram(vertex_shader_id, frag_shader_id, shader_program_id);

        if (!link_success)
        {
            HV_LOG_ERROR("Engine", "Creating rect without shader program (link went wrong)...");
            renderer->CreateRect();
        }
        else
        {
            renderer->CreateRect(shader_program_id);
        }
    }

    auto end_frame_time = std::chrono::steady_clock::now();

    while (!renderer->ShouldCloseWindow())
    {
        auto time_delta = (std::chrono::steady_clock::now() - end_frame_time).count();
        admin->Tick(time_delta);
        renderer->Tick(time_delta);

        end_frame_time = std::chrono::steady_clock::now();
    }

    delete renderer;
    delete admin;

    HV_LOG_INFO("Engine", "Heavenly Engine Shutdown...");

    /*

    


    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();

    while (!glfwWindowShouldClose(window)) {

        
    }*/

    return 0;
}
