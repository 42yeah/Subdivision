#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "standards.h"
#include "TriangleRenderer.h"
#include "TrunkRenderer.h"


int main(void) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCR_W, SCR_H, "Surface Subdivision", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    set_glfw_window(window);

    if (!gladLoadGL()) {
        std::cerr << "ERR! Failed to load GLAD." << std::endl;
        return -1;
    }

    // Global OpenGL configurations
    glEnable(GL_DEPTH_TEST);

    TrunkRenderer renderer;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        GLuint err = glGetError();
        if (err != GL_NONE) {
            std::cerr << "ERR! OpenGL error: " << err << std::endl;
        }

        renderer.render();

        glfwSwapBuffers(window);
    }

    return 0;
}
