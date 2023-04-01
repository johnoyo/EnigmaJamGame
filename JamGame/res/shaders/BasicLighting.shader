#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_tex_coord;
layout(location = 3) in float a_tex_id;

uniform mat4 u_VP;

out vec4 v_position;
out vec4 v_color;
out vec2 v_tex_coord;
out float v_tex_id;

void main()
{
	v_position = position;
	v_color = a_color;
	v_tex_coord = a_tex_coord;
	v_tex_id = a_tex_id;
	gl_Position = u_VP * position;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform vec3 u_LightPosition;

in vec4 v_position;
in vec4 v_color;
in vec2 v_tex_coord;
in float v_tex_id;

uniform sampler2D u_textures[32];

void main()
{
	int id = int(v_tex_id);
	float intensity = 2.0 / length(v_position.xy - u_LightPosition.xy);
	float multiplier = 50.0;
	vec4 finalColor = vec4(clamp(v_color.x * intensity * multiplier, 0.0, 1.0), clamp(v_color.y * intensity * multiplier, 0.0, 1.0), clamp(v_color.z * intensity * multiplier, 0.0, 1.0), v_color.w);
	color = texture(u_textures[id], v_tex_coord) * finalColor;
};