#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "ogl_utils/ogldev_math_3d.h"




//GLuint VBOs[3];

std::vector<GLuint> VBOs;


static void createTriangle(Vector3f vertices[3]) {
    GLuint VBO;
    glGenBuffers(1, &VBO); // Generate a new VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vector3f), vertices, GL_STATIC_DRAW);

    VBOs.push_back(VBO); // Add the new VBO to the vector
}

static void RenderSceneCB() {
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);

    // Loop through and draw each triangle
    for (GLuint vbo : VBOs) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3); // Draw 3 vertices
    }

    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}


static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;

    GLint Lengths[1];
    Lengths[0] = (GLint)strlen(pShaderText);

    glShaderSource(ShaderObj, 1, p, Lengths);

    //compiles shaderobject
    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

const char* pVSFileName = "/home/alfab/experiments/math_viz/src/shaders/T4/shader.vs";
const char* pFSFileName = "/home/alfab/experiments/math_viz/src/shaders/T4/shader.fs";

//load shader
static void CompileShaders()
{
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    std::string vs, fs;

    if (!ReadFile(pVSFileName, vs)) {
        exit(1);
    };

    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

    if (!ReadFile(pFSFileName, fs)) {
        exit(1);
    };

    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);

    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    //make shader program active
    glUseProgram(ShaderProgram);
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("multiple triangles");

    // Initialize GLEW
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    // Set up the shader
    CompileShaders();

    // Now create the triangles
    Vector3f Triangle1[3] = {
        Vector3f(0.5f, 0.5f, 0.0f),
        Vector3f(-0.5f, 0.5f, 0.0f), 
        Vector3f(0.0f, 0.1f, 0.0f)
    };
    createTriangle(Triangle1);

    Vector3f Triangle2[3] = {
        Vector3f(0.5f, -0.5f, 0.0f),   
        Vector3f(-0.5f, -0.5f, 0.0f),    
        Vector3f(0.0f, -0.1f, 0.0f)
    };
    createTriangle(Triangle2);

    Vector3f Triangle3[3] = {
        Vector3f(-0.75f, 0.5f, 0.0f),   
        Vector3f(-0.75f, -0.5f, 0.0f),    
        Vector3f(0.0f, 0.0f, 0.0f)
    };
    createTriangle(Triangle3);
    

    // Set clear color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Set up display callback
    glutDisplayFunc(RenderSceneCB);

    // Enter main loop
    glutMainLoop();

    return 0;
}
