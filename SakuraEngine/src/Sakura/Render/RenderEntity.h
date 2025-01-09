#pragma once

#include "Sakura/Core/Base.h"

#include "Sakura/Render/Buffer.h"
#include "Sakura/Render/InputLayout.h"
#include "Sakura/Render/RenderStructs.h"

namespace Sakura
{
    class RenderEntity
    {
    public:
        RenderEntity(const std::vector<Vertex>& vertices, const std::vector<Index>& indices);
        ~RenderEntity();

        void Render() const;

    private:
        Ref<InputLayout> m_InputLayout = nullptr;
        InputBinding m_InputBinding = {};
        Ref<Buffer> m_VertexBuffer = nullptr;
        Ref<Buffer> m_IndexBuffer = nullptr;
        uint32_t m_VertexCount = 0;
        uint32_t m_IndexCount = 0;
    };

}
