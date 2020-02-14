#include "Heavenly.h"
#include "EntityComponentSystem.h"
#include "Rendering.h"

#include <iostream>
#include <chrono>

#include "imgui.h"

int Heavenly::run(int argc, char** argv)
{
    std::cout << "Heavenly Engine Started..." << std::endl;

    std::cout << "Creating EntityAdmin..." << std::endl;

    auto admin = new EntityComponentSystem::WorldAdmin();

    std::cout << "Creating Renderer..." << std::endl;

    auto renderer = new Rendering::Renderer();
    renderer->InitContext(600, 400, false);

    auto end_frame_time = std::chrono::steady_clock::now();

    while (!renderer->ShouldCloseWindow())
    {
        auto time_delta = (std::chrono::steady_clock::now() - end_frame_time).count();
        std::cout << "Ticking with time_delta: " << time_delta << std::endl;
        admin->Tick(time_delta);
        renderer->Tick(time_delta);

        end_frame_time = std::chrono::steady_clock::now();
    }

    delete renderer;
    delete admin;

    std::cout << "Heavenly Engine Shutdown..." << std::endl;

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