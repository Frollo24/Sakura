#version 450 core

layout(location = 0) in vec2 v_TexCoord;

layout(location = 0) out vec4 o_Color;

layout(binding = 0) uniform sampler2D t_ScreenTexture;

void main() {
	o_Color = texture(t_ScreenTexture, v_TexCoord);
}
