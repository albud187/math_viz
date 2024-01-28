#version 330 core

//declare what attribute to take in
//vector of 3 floating points (vec3) of name Position

layout (location = 0) in vec3 Position;

//check in and out qualifier of glVertexAttribPointer
void main()
{
    gl_Position = vec4(0.25 * Position.x, 0.25 * Position.y, Position.z, 0.5);
}