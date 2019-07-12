#pragma once

#include <string>

namespace yunikEngine {
    enum class ShaderType {
        COMPUTE_SHADER,
        VERTEX_SHADER,
        TESS_CONTROL_SHADER,
        TESS_EVALUATION_SHADER,
        GEOMETRY_SHADER,
        FRAGMENT_SHADER
    };

    class Shader {
    friend class ShaderProgram;

    public:
        ~Shader (void);

        bool load (const std::string& shaderSrc, const ShaderType& shaderType);

    private:
        unsigned int shader = 0;
    };

    class ShaderProgram {
    public:
        ~ShaderProgram (void);

        bool init (void);

        void attachShader (const Shader& shader) const;
        bool link (void) const;
    
    private:
        unsigned int program = 0;
    };
}
