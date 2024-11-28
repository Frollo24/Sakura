#version 460 core
layout(location = 0) in vec3 v_Color;
layout(location = 1) in vec2 v_TexCoord;

layout(location = 0) out vec4 o_Color;

layout(binding = 0) uniform sampler2D u_Texture;

void main(){
	vec4 texColor = texture(u_Texture, v_TexCoord);
	o_Color = texColor * vec4(v_Color, 1.0);
}