#version 300 es

layout(location = 0) in vec2 inPosition;
//layout(location = 1) in vec4 inColor;

uniform vec4 color;
uniform float scale;

out vec4 fragColor;

void main() {
    gl_Position = vec4(inPosition, 0, 1);
    //outColor = color;
    fragColor = color;
}