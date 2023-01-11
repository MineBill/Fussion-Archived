#version 420 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec3 a_normal;

out vec2 s_texcoord;
out vec3 s_normal;
out vec3 s_frag_position;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
    s_texcoord = vec2(a_texcoord.x, 1.0 - a_texcoord.y);
    s_frag_position = vec3(u_model * vec4(a_position, 1.0));

    // PERFORMANCE: This should be done on the CPU
    s_normal = mat3(transpose(inverse(u_model))) * a_normal;
}
