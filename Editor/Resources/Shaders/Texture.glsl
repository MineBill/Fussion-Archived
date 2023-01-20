#type vertex
#version 460 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TextureCoords;

out vec4 s_Color;
out vec2 s_TextureCoords;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

void main()
{
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
    s_TextureCoords = a_TextureCoords;
    s_Color = a_Color;
}

#type fragment
#version 460 core
out vec4 FragColor;

in vec4 s_Color;
in vec2 s_TextureCoords;

void main()
{
    FragColor = vec4(s_TextureCoords, 0.0f, 1.0f) * s_Color;
}
