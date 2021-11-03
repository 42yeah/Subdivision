#pragma once

#include <GLFW/glfw3.h>

// Professionals have standards.

#define SCR_W 1280
#define SCR_H 720
#define ASPECT ((float) SCR_W / SCR_H)

void set_glfw_window(GLFWwindow *window);

GLFWwindow *get_glfw_window();


// 例子 1：正方体
// #define MODEL_PATH "models/shape/shape.obj"
// #define MTL_SEARCH_PATH "models/shape/"

// 例子 2：ppt 里的图像（但我不太会用 Blender，因此去不掉中间的边）
// #define MODEL_PATH "models/test/test.obj"
// #define MTL_SEARCH_PATH "models/test/"

// 例子 3：Blender 的 Suzanne 
#define MODEL_PATH "models/suzanne/suzanne.obj"
#define MTL_SEARCH_PATH "models/suzanne/"

