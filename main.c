#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(int argc, char* argv[]) {

	printf("Heavenly Engine Started...\n");

	if (!glfwInit()) {
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Heavenly Game Engine", NULL, NULL);
	if (!window) {
		printf("Could not create glfw window. Exiting.");
		return -1;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	printf("Heavenly Engine Shutdown...\n");
	glfwTerminate();

	return 0;
}