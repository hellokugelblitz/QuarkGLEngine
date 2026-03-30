#version 330 core
layout(location = 0) in vec3 aPos;  // position from your vertex array
layout(location = 1) in vec2 aTexCoord;

uniform mat4 model;
out vec2 TexCoord;

void main()
{
    gl_Position = model * vec4(aPos, 1.0); // output to the pipeline and apply the model transform
    TexCoord = aTexCoord;
}
