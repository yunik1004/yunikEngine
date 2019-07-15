#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace yunikEngine {
    class Texture;

    struct Vertex {
        glm::vec3 m_pos;
        glm::vec2 m_tex;
        glm::vec3 m_normal;

        Vertex (const glm::vec3& pos, const glm::vec2& tex, const glm::vec3& normal) {
            m_pos = pos;
            m_tex = tex;
            m_normal = normal;
        }
    };

    class Mesh {
    public:
        ~Mesh (void);

        bool load (const std::string& fileName);

        void render (void);

    private:
        bool initFromScene (const void* pScene, const std::string& fileName);
        void initMesh (unsigned int index, const void* paiMesh);
        bool initMaterials (const void* pScene, const std::string& fileName);

        struct MeshEntry {
            ~MeshEntry (void);

            unsigned int VA = 0xffffffff;
            unsigned int VB = 0xffffffff;
            unsigned int IB = 0xffffffff;

            void init (const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

            unsigned int numIndices = 0;
            unsigned int materialIndex = 0xffffffff;
        };

        std::vector<MeshEntry> m_Entries;
        std::vector<Texture*> m_Textures;
    };
}
