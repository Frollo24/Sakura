#include "skrpch.h"
#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Sakura
{
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
        : m_Vertices(vertices), m_Indices(indices), m_RenderEntity(CreateRef<RenderEntity>(vertices, indices))
    {
    }

    Mesh::Mesh(const Mesh& other)
    {
        m_Vertices = other.m_Vertices;
        m_Indices = other.m_Indices;
        m_RenderEntity = CreateRef<RenderEntity>(m_Vertices, m_Indices);
    }

    Mesh::~Mesh()
    {
        m_RenderEntity = nullptr;
        m_Vertices.clear();
        m_Indices.clear();
    }

    Model::Model(const std::string& path)
    {
        Assimp::Importer import;
        const aiScene * scene = import.ReadFile(path,
            aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            SKR_CORE_ERROR("ASSIMP: {}", import.GetErrorString());
            return;
        }

        LoadMeshes(scene);
    }

    Model::~Model()
    {
        m_Meshes.clear();
    }

    void Model::LoadMeshes(const aiScene* scene)
    {
        m_Meshes.reserve(scene->mNumMeshes);
        for (size_t i = 0; i < scene->mNumMeshes; i++)
        {
            const aiMesh* mesh = scene->mMeshes[i];
            m_Meshes.push_back(ProcessMesh(mesh, scene));
        }
    }

    Mesh Model::ProcessMesh(const aiMesh* mesh, const aiScene* scene)
    {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        for (int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;

            glm::vec3 position;
            position.x = mesh->mVertices[i].x;
            position.y = mesh->mVertices[i].y;
            position.z = mesh->mVertices[i].z;
            vertex.Position = position;

            glm::vec3 normal;
            normal.x = mesh->mNormals[i].x;
            normal.y = mesh->mNormals[i].y;
            normal.z = mesh->mNormals[i].z;
            vertex.Normal = normal;

            if (mesh->mTangents)
            {
                glm::vec3 tangent;
                tangent.x = mesh->mTangents[i].x;
                tangent.y = mesh->mTangents[i].y;
                tangent.z = mesh->mTangents[i].z;
                vertex.Tangent = tangent;

                glm::vec3 bitangent;
                bitangent.x = mesh->mBitangents[i].x;
                bitangent.y = mesh->mBitangents[i].y;
                bitangent.z = mesh->mBitangents[i].z;
                vertex.Bitangent = bitangent;
            }

            if (mesh->mTextureCoords[0])
            {
                glm::vec2 texCoord;
                texCoord.x = mesh->mTextureCoords[0][i].x;
                texCoord.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoord = texCoord;
            }

            vertices.push_back(vertex);
        }

        for (uint32_t i = 0; i < mesh->mNumFaces; i++)
        {
            const aiFace face = mesh->mFaces[i];
            for (uint32_t j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        return Mesh(vertices, indices);
    }
}