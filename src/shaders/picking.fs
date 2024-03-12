#version 330

uniform vec3 uniColor; // The unique color for the object
out vec4 fragColor;

void main() {
    fragColor = vec4(uniColor, 1.0); // Use the unique color directly
}
