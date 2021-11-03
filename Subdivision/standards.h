#pragma once

#include <GLFW/glfw3.h>

// Professionals have standards.

#define SCR_W 1280
#define SCR_H 720
#define ASPECT ((float) SCR_W / SCR_H)

void set_glfw_window(GLFWwindow *window);

GLFWwindow *get_glfw_window();

// Slated to be DYNAMICALLY LOADED in the future.
#define MODEL_PATH "models/shape/shape.obj"
#define MTL_SEARCH_PATH "models/shape/"
