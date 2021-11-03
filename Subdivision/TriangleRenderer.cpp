#include "TriangleRenderer.h"

TriangleRenderer::TriangleRenderer() {
    program.init("shaders/default.vert", "shaders/default.frag");
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    float data[] = {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

    // Camera setup
    eye = glm::vec3(0.0f, 0.0f, -2.0f);
    view = glm::lookAt(eye, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    perspective = glm::perspective(glm::radians(45.0f), ASPECT, 0.01f, 20.0f);
}

void TriangleRenderer::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program.use();
    glUniformMatrix4fv(program.loc("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(program.loc("perspective"), 1, GL_FALSE, glm::value_ptr(perspective));
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
