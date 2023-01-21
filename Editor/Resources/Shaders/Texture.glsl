#type vertex
#version 460 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TextureCoords;
layout (location = 3) in float a_TextureIndex;

out vec4 s_Color;
out vec2 s_TextureCoords;
out float s_TextureIndex;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

void main()
{
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
    s_TextureCoords = a_TextureCoords;
    s_Color = a_Color;
    s_TextureIndex = a_TextureIndex;
}

#type fragment
#version 460 core
out vec4 FragColor;

in vec4 s_Color;
in vec2 s_TextureCoords;
in float s_TextureIndex;

uniform sampler2D u_Textures[32];

void main()
{
    FragColor = texture(u_Textures[int(s_TextureIndex)], s_TextureCoords) * s_Color;
}
