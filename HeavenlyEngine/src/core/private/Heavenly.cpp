#include "Heavenly.h"
#include "EntityComponentSystem.h"
#include "GUI.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"

int Heavenly::run(int argc, char** argv)
{
    std::cout << "Heavenly Engine Started..." << std::endl;

    std::cout << "Creating EntityAdmin" << std::endl;

    auto admin = EntityComponentSystem::WorldAdmin();

    std::cout << "Admin created... Adding GUISystem to it and ticking once..." << std::endl;

    admin.RegisterSystem(new GUI::GUISystem());

    admin.Tick(0.5);

    std::cout << "Tick successful." << std::endl;

    /*

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Could not initialize glad. Exiting.");
        return -1;
    }


    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }*/

    std::cout << "Heavenly Engine Shutdown..." << std::endl;

    return 0;
}