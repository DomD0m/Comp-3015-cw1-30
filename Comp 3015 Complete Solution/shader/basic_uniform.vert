#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexCoord;

//sending info to the frag.
flat out vec3 Position;
flat out vec3 Normal;
flat out vec2 TexCoord;

//declaring uniforms
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;





void main()
{
    TexCoord=VertexTexCoord;
    Normal = normalize(NormalMatrix*VertexNormal);
    Position = (ModelViewMatrix*vec4(VertexPosition,1.0)).xyz;


    gl_Position = MVP*vec4(VertexPosition,1.0);
}
