#include "Program.h"
#include <fstream>
#include <sstream>


GLuint compile(GLuint type, std::string path) {
    GLuint shader = glCreateShader(type);

    std::ifstream reader(path);
    if (!reader.good()) {
        std::cerr << "ERR! Bad shader path: " << path << std::endl;
        return 0;
    }
    std::stringstream ss;
    ss << reader.rdbuf();
    std::string src = ss.str();
    const char *raw = src.c_str();
    glShaderSource(shader, 1, &raw, nullptr);
    glCompileShader(shader);
    char log[512] = { 0 };
    glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
    std::cout << path << " info log: " << log << std::endl;

    return shader;
}

void Program::init(std::string vpath, std::string fpath) {
    program = glCreateProgram();
    glAttachShader(program, compile(GL_VERTEX_SHADER, vpath));
    glAttachShader(program, compile(GL_FRAGMENT_SHADER, fpath));
    glLinkProgram(program);

    char log[512] = { 0 };
    glGetProgramInfoLog(program, sizeof(log), nullptr, log);
    std::cout << "Program info log: " << log << std::endl;
}

void Program::use() {
    glUseProgram(program);
}

GLuint Program::loc(std::string uniform_name) {
    auto pos = uniform_locations.find(uniform_name);
    if (pos == uniform_locations.end()) {
        GLint pos = glGetUniformLocation(program, uniform_name.c_str());
        if (pos < 0) {
            std::cerr << "ERR! Uniform not found: " << uniform_name << std::endl;
            return 0;
        }
        uniform_locations[uniform_name] = (GLuint) pos;
        return (GLuint) pos;
    }
    return pos->second;
}
