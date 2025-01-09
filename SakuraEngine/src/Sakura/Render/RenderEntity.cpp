#include "skrpch.h"
#include "RenderEntity.h"

#include "Renderer.h"
#include "RenderDevice.h"
#include "RenderContext.h"

namespace Sakura
{
    RenderEntity::RenderEntity(const std::vector<Vertex>& vertices, const std::vector<Index>& indices)
        : m_VertexCount(vertices.size()), m_IndexCount(indices.size())
    {
        BufferDescription vertexDescription = {};
        vertexDescription.Type = BufferType::Vertex;
        vertexDescription.Size = sizeof(Vertex) * m_VertexCount;
        vertexDescription.Data = (void*)(vertices.data());
        m_VertexBuffer = Renderer::GetDevice()->CreateBuffer(vertexDescription);

        if (m_IndexCount)
        {
            BufferDescription indexDescription = {};
            indexDescription.Type = BufferType::Index;
            indexDescription.Size = sizeof(Index) * m_IndexCount;
            indexDescription.Data = (void*)(indices.data());
            m_IndexBuffer = Renderer::GetDevice()->CreateBuffer(indexDescription);
        }

        m_InputBinding = GetRenderEntityInputBinding();
        m_InputLayout = InputLayout::Create(std::vector<InputBinding>{ m_InputBinding });
    }

    RenderEntity::~RenderEntity()
    {
        m_IndexBuffer = nullptr;
        m_VertexBuffer = nullptr;
    }

    void RenderEntity::Render() const
    {
        Renderer::GetContext()->SetInputLayout(m_InputLayout);
        Renderer::GetContext()->BindVertexBuffer(m_VertexBuffer, m_InputBinding);

        if (m_IndexBuffer)
        {
            Renderer::GetContext()->BindIndexBuffer(m_IndexBuffer);
            Renderer::GetContext()->DrawIndexed(m_IndexCount, 1, 0, 0, 0);
        }
        else
        {
            Renderer::GetContext()->Draw(m_VertexCount, 1, 0, 0);
        }
    }
}