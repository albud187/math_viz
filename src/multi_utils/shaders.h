
#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <string.h>

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>


void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);

void CompileShaders(const char* pVSFileName, const char* pFSFileName, GLuint gWVPLocation);

#endif