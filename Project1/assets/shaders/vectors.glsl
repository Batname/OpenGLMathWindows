#version 330 core
layout (location = 0) in vec3 position; // The position variable has attribute position 0
layout (location = 1) in vec3 color;

out vec4 vertexColor; // Specify a color output to the fragment shader

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
    if (position.x < 0.01f && position.x > -0.01f)
    {
        gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0);

    }
    else
    {
        gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
    }
    vertexColor = vec4(color, 1.0f);
}
