#include <yunikEngine/shader.hpp>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

namespace yunikEngine {
    Shader::~Shader (void) {
        if (shader != 0) {
            glDeleteShader(shader);
        }
    }

    bool Shader::load (const Shader::Type shaderType, const std::string& shaderSrc) {
        GLenum stype;
        switch (shaderType) {
            case Type::COMPUTE_SHADER:
                stype = GL_COMPUTE_SHADER;
                break;
            case Type::VERTEX_SHADER:
                stype = GL_VERTEX_SHADER;
                break;
            case Type::TESS_CONTROL_SHADER:
                stype = GL_TESS_CONTROL_SHADER;
                break;
            case Type::TESS_EVALUATION_SHADER:
                stype = GL_TESS_EVALUATION_SHADER;
                break;
            case Type::GEOMETRY_SHADER:
                stype = GL_GEOMETRY_SHADER;
                break;
            case Type::FRAGMENT_SHADER:
                stype = GL_FRAGMENT_SHADER;
                break;
        }

        shader = glCreateShader(stype);
        if (shader == 0) {
            fprintf_s(stderr, "OpenGL error: Cannot create shader\n");
            return false;
        }

        const char* shaderSrc_char = shaderSrc.c_str();

        glShaderSource(shader, 1, &shaderSrc_char, nullptr);

        GLint success;
        
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
            fprintf_s(stderr, "Shader(%d) compiling error: %s\n", stype, infoLog);
            return false;
        }

        return true;
    }

    ShaderProgram::~ShaderProgram (void) {
        if (program != 0) {
            glDeleteProgram(program);
        }
    }

    bool ShaderProgram::init (void) {
        program = glCreateProgram();
        if (program != 0) {
            return false;
        }
    }

    void ShaderProgram::attachShader (const Shader& shader) const {
        glAttachShader(program, shader.shader);
    }

    bool ShaderProgram::link (void) const {
        GLint success;
        GLchar infoLog[1024];

        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
            fprintf_s(stderr, "Shader program linking error: %s\n", infoLog);
            return false;
        }

        glValidateProgram(program);
        glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
            fprintf_s(stderr, "Invalid shader program: %s\n", infoLog);
            return false;
        }

        return true;
    }
}
