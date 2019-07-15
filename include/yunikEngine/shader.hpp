#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

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

        void setBool (const std::string& name, const bool value) const;
        void setInt (const std::string& name, const int value) const;
        void setFloat (const std::string& name, const float value) const;
        void setVec2 (const std::string& name, const glm::vec2 value) const;
        void setVec3 (const std::string& name, const glm::vec3 value) const;
        void setVec4 (const std::string& name, const glm::vec4 value) const;
        void setMat2 (const std::string& name, const glm::mat2 value) const;
        void setMat3 (const std::string& name, const glm::mat3 value) const;
        void setMat4 (const std::string& name, const glm::mat4 value) const;
    
    private:
        unsigned int program = 0;

        std::vector<unsigned int> shaderIDs;
    };
}
