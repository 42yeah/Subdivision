#pragma once

#include <GLFW/glfw3.h>

// Professionals have standards.

#define SCR_W 1280
#define SCR_H 720
#define ASPECT ((float) SCR_W / SCR_H)

void set_glfw_window(GLFWwindow *window);

GLFWwindow *get_glfw_window();


// ���� 1��������
// #define MODEL_PATH "models/shape/shape.obj"
// #define MTL_SEARCH_PATH "models/shape/"

// ���� 2��ppt ���ͼ�񣨵��Ҳ�̫���� Blender�����ȥ�����м�ıߣ�
// #define MODEL_PATH "models/test/test.obj"
// #define MTL_SEARCH_PATH "models/test/"

// ���� 3��Blender �� Suzanne 
#define MODEL_PATH "models/suzanne/suzanne.obj"
#define MTL_SEARCH_PATH "models/suzanne/"

