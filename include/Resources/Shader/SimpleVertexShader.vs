#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

out vec3 fragmentColor;

uniform mat4 MVP;
uniforn vec3 color;
  
void main()
{
  gl_Position = MVP * vec4(vertexPosition_modelspace,1);

  fragmentColor = color;
}