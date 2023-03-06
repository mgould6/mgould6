#version 330 core
out vec4 FragColor;

// inputs the color from the vertex shader
in vec3 color;

in vec2 texCoord;

uniform sampler2d tex0;

void main()
{
	FragColor = vec4(tex0, texCoord);
};