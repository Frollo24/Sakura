#pragma once

#include "Sakura/Core/Base.h"
#include "Sakura/Render/RenderEntity.h"

struct aiScene;
struct aiMesh;

namespace Sakura
{
    class Mesh
    {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<Index>& indices);
        Mesh(const Mesh& other);
        ~Mesh();

        inline const std::vector<Vertex>& GetVertices() const { return m_Vertices; }
        inline const std::vector<Index>& GetIndices() const { return m_Indices; }
        inline const Ref<RenderEntity>& GetRenderEntity() const { return m_RenderEntity; }

        inline void Render() const { m_RenderEntity->Render(); }

    private:
        std::vector<Vertex> m_Vertices;
        std::vector<Index> m_Indices;
        Ref<RenderEntity> m_RenderEntity = nullptr;
    };

    class Model
    {
    public:
        Model(const std::string& path);
        ~Model();

        inline const std::vector<Mesh>& GetMeshes() const { return m_Meshes; }

    private:
        void LoadMeshes(const aiScene* scene);
        Mesh ProcessMesh(const aiMesh* mesh, const aiScene* scene);

    private:
        std::vector<Mesh> m_Meshes;
    };
}
