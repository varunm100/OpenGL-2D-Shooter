#SHADER VERTEX
#version 450 core

layout(location = 0)  in vec3 position;
layout(location = 1)  in vec2 texCoord;

out vec2 texFragCoord;

uniform mat4 model;
uniform mat4 projection;

void main() {
	texFragCoord = texCoord;
	gl_Position = projection * model * vec4(position.xyz, 1.0f);
};

#SHADER FRAGMENT
#version 450 core

in vec2 texFragCoord;

out vec4 fragColor;

uniform sampler2D quadTexture;

void main() {
	fragColor = texture(quadTexture, texFragCoord);
};