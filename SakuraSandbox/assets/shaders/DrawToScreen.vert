#version 450 core

layout(location = 0) out vec2 v_TexCoord;

const vec2 ScreenCoords[6] = vec2[](
	vec2(-1.0, -1.0),
	vec2(1.0, -1.0),
	vec2(1.0, 1.0),
	vec2(1.0, 1.0),
	vec2(-1.0, 1.0),
	vec2(-1.0, -1.0)
);

void main() {
	v_TexCoord = ScreenCoords[gl_VertexID];
	gl_Position = vec4(v_TexCoord, 0.0, 1.0);
	v_TexCoord.y = -v_TexCoord.y;
	v_TexCoord = 0.5 * v_TexCoord + 0.5;
}
