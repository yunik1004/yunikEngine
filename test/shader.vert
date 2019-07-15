#version 440 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 Projection;
uniform mat4 View;

void main(){
    gl_Position = Projection * View * vec4(vertexPosition_modelspace, 1);
}
