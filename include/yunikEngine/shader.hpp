#pragma once

#include <string>
#include <vector>

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

        bool loadSource (const Type shaderType, const std::string& shaderSrc);
        bool load (const Type shaderType, const std::string& fileName);

    private:
        unsigned int shader = 0;
    };

    class ShaderProgram {
    public:
        ~ShaderProgram (void);

        bool init (void);

        void attachShader (const Shader& shader);
        bool link (void) const;

        void use (void) const;
    
    private:
        unsigned int program = 0;

        std::vector<unsigned int> shaderIDs;
    };
}
