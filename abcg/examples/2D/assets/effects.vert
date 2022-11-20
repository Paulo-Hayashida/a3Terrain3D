#version 300 es

layout(location = 0) in vec2 inPosition;
//layout(location = 1) in vec4 inColor;

uniform vec4 color;
uniform float scale;

out vec4 fragColor;

void main() {
    vec2 newPosition = vec2(inPosition.x, inPosition.y);
    gl_Position = vec4(newPosition, 0, 1);
    fragColor = color;
}