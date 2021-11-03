#include "standards.h"


GLFWwindow *window_instance = nullptr;

void set_glfw_window(GLFWwindow* window) {
    window_instance = window;    
}

GLFWwindow* get_glfw_window() {
    return window_instance;
}
