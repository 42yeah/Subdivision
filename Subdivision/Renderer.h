#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "standards.h"
#include "Program.h"


class Renderer {
public:
    virtual void render() = 0;
};
