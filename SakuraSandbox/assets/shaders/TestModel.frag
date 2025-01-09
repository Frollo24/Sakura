#version 460 core
layout(location = 0) in vec3 v_Normal;
layout(location = 1) in vec2 v_TexCoord;

layout(location = 0) out vec4 o_Color;

layout(binding = 0) uniform sampler2D u_Texture;
uniform vec4 u_LightDir;

void main(){
	vec4 texColor = texture(u_Texture, v_TexCoord);
	vec3 normalColor = normalize(v_Normal) * 0.5 + 0.5;
	normalColor *= max(dot(u_LightDir.xyz, v_Normal), 0.1);

	o_Color = texColor * vec4(normalColor, 1.0);
}
