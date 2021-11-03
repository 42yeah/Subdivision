#include "TrunkRenderer.h"


TrunkRenderer::TrunkRenderer() {
    program.init("shaders/model/phong.vert", "shaders/model/phong.frag");
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    mesh.init(MODEL_PATH, MTL_SEARCH_PATH);
    vertices = mesh.to_vertices();
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, ((void *) (sizeof(float) * 3)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, ((void *) (sizeof(float) * 6)));

    // Camera setup
    eye = glm::vec3(2.0f, 2.0f, -5.0f);
    center = glm::vec3(0.0f);
    eye_dir = glm::normalize(center - eye);
    view = glm::lookAt(eye, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    perspective = glm::perspective(glm::radians(45.0f), ASPECT, 0.01f, 20.0f);

    // Subdivide event handle
    subdividing = false;
    outlining = false;

    drawing_outline = true;
}

void TrunkRenderer::render() {
    if (glfwGetKey(get_glfw_window(), GLFW_KEY_SPACE)) {
        if (!subdividing) {
            mesh.butterfly_subdivide(eye_dir);
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);

            vertices = mesh.to_vertices();

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, nullptr);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, ((void*)(sizeof(float) * 3)));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, ((void*)(sizeof(float) * 6)));
            subdividing = true;
        }
    } else {
        subdividing = false;
    }
    if (glfwGetKey(get_glfw_window(), GLFW_KEY_E)) {
        if (!outlining) {
            drawing_outline = !drawing_outline;
            outlining = true;
        }
    } else {
        outlining = false;
    }

    glm::mat4 model(1.0f);
    model = glm::rotate(model, (float) glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program.use();
    glUniformMatrix4fv(program.loc("model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(program.loc("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(program.loc("perspective"), 1, GL_FALSE, glm::value_ptr(perspective));
    glBindVertexArray(VAO);
    if (drawing_outline) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    glDrawArrays(GL_TRIANGLES, 0, (int) vertices.size());
}
