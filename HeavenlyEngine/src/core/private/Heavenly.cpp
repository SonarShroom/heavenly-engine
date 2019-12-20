#include "Heavenly.h"

#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"

int Heavenly::run(int argc, char** argv)
{
    printf("Heavenly Engine Started...\n");

    if (!glfwInit()) {
        printf("Could not init glfw. Exiting.");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Heavenly Game Engine", NULL, NULL);
    if (!window) {
        printf("Could not create glfw window. Exiting.");
        return -1;
    }

    glfwMakeContextCurrent(window);

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
    }

    printf("Heavenly Engine Shutdown...\n");

    return 0;
}