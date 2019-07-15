#include <yunikEngine/shader.hpp>

#include <fstream>
#include <sstream>
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

    bool Shader::loadSource (const Shader::Type shaderType, const std::string& shaderSrc) {
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
            GLint infoLogLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
            
            GLchar* infoLog = new GLchar[infoLogLength];
            glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog);
            fprintf_s(stderr, "Shader(%d) compiling error: %s\n", stype, infoLog);

            delete[] infoLog;
            return false;
        }

        return true;
    }

    bool Shader::load (const Shader::Type shaderType, const std::string& fileName) {
        std::ifstream fs(fileName, std::ios::in);

        std::string shaderSrc;

        if (fs.is_open()) {
            std::stringstream sstr;
            sstr << fs.rdbuf();
            shaderSrc = sstr.str();

            fs.close();
        }

        return loadSource(shaderType, shaderSrc);
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

    void ShaderProgram::attachShader (const Shader& shader) {
        glAttachShader(program, shader.shader);
        shaderIDs.push_back(shader.shader);
    }

    bool ShaderProgram::link (void) const {
        GLint success;
        bool res = true;

        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            GLint infoLogLength;
            glGetShaderiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
            GLchar* infoLog = new GLchar[infoLogLength];

            glGetProgramInfoLog(program, infoLogLength, nullptr, infoLog);
            fprintf_s(stderr, "Shader program linking error: %s\n", infoLog);

            delete[] infoLog;
            res = false;
        }

        glValidateProgram(program);
        glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
        if (!success) {
            GLint infoLogLength;
            glGetShaderiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
            GLchar* infoLog = new GLchar[infoLogLength];

            glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
            fprintf_s(stderr, "Invalid shader program: %s\n", infoLog);

            delete[] infoLog;
            res = false;
        }

        for (int i = 0; i < shaderIDs.size(); ++i) {
            glDetachShader(program, shaderIDs[i]);
        }

        return res;
    }

    void ShaderProgram::use (void) const {
        glUseProgram(program);
    }
}
