#include <yunikEngine/mesh.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <yunikEngine/texture.hpp>

namespace yunikEngine {
    Mesh::~Mesh (void) {
        for (unsigned int i = 0; i < m_Textures.size(); ++i) {
            delete m_Textures[i];
        }
    }

    bool Mesh::load (const std::string& fileName) {
        Assimp::Importer importer;

        const aiScene* pScene = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

        bool res = false;

        if (pScene) {
            res = initFromScene(pScene, fileName);
        } else {
            fprintf_s(stderr, "Error parsing '%s': %s\n", fileName.c_str(), importer.GetErrorString());
        }

        return res;
    }

    void Mesh::render (void) {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        for (unsigned int i = 0; i < m_Entries.size(); ++i) {
            glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);

            const unsigned int materialIndex = m_Entries[i].materialIndex;
            if (materialIndex < m_Textures.size() && m_Textures[materialIndex]) {
                m_Textures[materialIndex]->bind(0);
            }

            glDrawElements(GL_TRIANGLES, m_Entries[i].numIndices, GL_UNSIGNED_INT, 0);
        }

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
    }

    bool Mesh::initFromScene (const void* pScene, const std::string& fileName) {
        const aiScene* pScene_ai = static_cast<const aiScene*>(pScene);

        m_Entries.resize(pScene_ai->mNumMeshes);
        m_Textures.resize(pScene_ai->mNumMaterials);

        // Initialize the meshes in the scene
        for (unsigned int i = 0; i < m_Entries.size(); ++i) {
            const aiMesh* paiMesh = pScene_ai->mMeshes[i];
            initMesh(i, paiMesh);
        }
        
        return initMaterials(pScene, fileName);
    }

    void Mesh::initMesh (unsigned int index, const void* paiMesh) {
        const aiMesh* paiMesh_ai = static_cast<const aiMesh*>(paiMesh);

        m_Entries[index].materialIndex = paiMesh_ai->mMaterialIndex;

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        const aiVector3D zero3D(0.0f, 0.0f, 0.0f);

        for (unsigned int i = 0; i < paiMesh_ai->mNumVertices; ++i) {
            const aiVector3D* pPos = &(paiMesh_ai->mVertices[i]);
            const aiVector3D* pNormal = &(paiMesh_ai->mNormals[i]);
            const aiVector3D* pTexCoord = paiMesh_ai->HasTextureCoords(0) ? &(paiMesh_ai->mTextureCoords[0][i]) : &zero3D;

            Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z), glm::vec2(pTexCoord->x, pTexCoord->y), glm::vec3(pNormal->x, pNormal->y, pNormal->z));

            vertices.push_back(v);
        }

        for (unsigned int i = 0; i < paiMesh_ai->mNumFaces; ++i) {
            const aiFace& face = paiMesh_ai->mFaces[i];
            
            assert(face.mNumIndices == 3); // due to triangulation

            indices.push_back(face.mIndices[0]);
            indices.push_back(face.mIndices[1]);
            indices.push_back(face.mIndices[2]);
        }

        m_Entries[index].init(vertices, indices);
    }

    bool Mesh::initMaterials (const void* pScene, const std::string& fileName) {
        const aiScene* pScene_ai = static_cast<const aiScene*>(pScene);

        for (unsigned int i = 0; i < pScene_ai->mNumMaterials; ++i) {
            const aiMaterial* pMaterial = pScene_ai->mMaterials[i];

            m_Textures[i] = nullptr;
            if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
                aiString path;

                if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path, nullptr, nullptr, nullptr, nullptr, nullptr) == AI_SUCCESS) {
                    std::string fullPath = path.data; // To be modified

                    m_Textures[i] = new Texture();
                    if (!m_Textures[i]->load(Texture::Type::TEXTURE_2D, fullPath)) {
                        fprintf_s(stderr, "Error loading texture '%s'\n", fullPath.c_str());
                        delete m_Textures[i];
                        return false;
                    }
                }
            }
        }

        return true;
    }

    Mesh::MeshEntry::~MeshEntry (void) {
        if (VB != 0xffffffff) {
            glDeleteBuffers(1, &VB);
        }

        if (IB != 0xffffffff) {
            glDeleteBuffers(1, &IB);
        }
    }

    void Mesh::MeshEntry::init (const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
        numIndices = static_cast<unsigned int>(indices.size());

        glGenVertexArrays(1, &VA);
	    glBindVertexArray(VA);

        glGenBuffers(1, &VB);
        glBindBuffer(GL_ARRAY_BUFFER, VB);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &IB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, &indices[0], GL_STATIC_DRAW);
    }
}
