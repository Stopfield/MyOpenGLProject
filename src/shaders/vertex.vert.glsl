#version 400 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 MyColor;
out vec2 TexCoord;

void main()
{
    // VertexColor = vec4(0.5f, 0.2f, 0.5f, 1.0f);
    gl_Position = vec4(aPos, 1.0);
    MyColor = aColor;
    TexCoord = aTexCoord;
}