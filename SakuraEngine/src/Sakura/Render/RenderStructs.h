#pragma once

#include <glm/glm.hpp>
#include <Sakura/Render/InputLayout.h>

namespace Sakura
{
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal = glm::vec3(0, 0, 1);
        glm::vec3 Tangent = glm::vec3(1, 0, 0);
        glm::vec3 Bitangent = glm::vec3(0, 1, 0);
        glm::vec2 TexCoord = glm::vec2(0, 0);
    };

    using Index = uint32_t;

    inline InputBinding GetRenderEntityInputBinding()
    {
        return InputBinding{
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float3, "a_Normal"},
            {ShaderDataType::Float3, "a_Tangent"},
            {ShaderDataType::Float3, "a_Bitangent"},
            {ShaderDataType::Float2, "a_TexCoord"},
        };
    }
}