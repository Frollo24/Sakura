#version 460 core
layout(location = 0) in vec3 v_Normal;
layout(location = 1) in vec2 v_TexCoord;

layout(location = 0) out vec4 o_Color;

layout(binding = 0) uniform sampler2D u_Texture;

void main(){
	vec4 texColor = texture(u_Texture, v_TexCoord);
	vec3 normalColor = v_Normal * 0.5 + 0.5;

	o_Color = texColor * vec4(normalColor, 1.0);
}
