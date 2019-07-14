#pragma once

#include <string>

namespace yunikEngine {
    class Shader {
    friend class ShaderProgram;

    public:
        enum class Type {
            COMPUTE_SHADER,
            VERTEX_SHADER,
            TESS_CONTROL_SHADER,
            TESS_EVALUATION_SHADER,
            GEOMETRY_SHADER,
            FRAGMENT_SHADER
        };

        ~Shader (void);

        bool load (const Type shaderType, const std::string& shaderSrc);

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
