#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "standards.h"
#include "TriangleRenderer.h"


int main(void) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCR_W, SCR_H, "Surface Subdivision", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cerr << "ERR! Failed to load GLAD." << std::endl;
        return -1;
    }

    // Global OpenGL configurations
    glEnable(GL_DEPTH_TEST);

    TriangleRenderer renderer;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        renderer.render();

        glfwSwapBuffers(window);
    }

    return 0;
}
