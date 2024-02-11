
#include <stdio.h>
#include <string.h>

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ogl_utils/ogldev_math_3d.h"
#include "programs/T15/camera.h"
#include "programs/T15/world_transform.h"
#include "programs/T15/constants.h"
#include "programs/T15/shaders.h"

GLuint VBO;
GLuint IBO;
GLuint gWVPLocation;

WorldTrans CubeWorldTransform;

WorldTrans CubeWorldTransform2;
Camera GameCamera(WINDOW_WIDTH, WINDOW_HEIGHT, CAMERA_POS, CAMERA_TARGET, CAMERA_UP);

PersProjInfo persProjInfo = { FOV, WINDOW_WIDTH, WINDOW_HEIGHT, Z_NEAR, Z_FAR };

int TEST = 0;

float dx = 0.001f;
void DrawCube() {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Also clear the depth buffer

    // Initialize and use the camera
    GameCamera.OnRender();
    Matrix4f Projection;
    Matrix4f View = GameCamera.GetMatrix();
    Projection.InitPersProjTransform(persProjInfo);

    // First Cube Transformations
    if (TEST == 0) {
        CubeWorldTransform.SetPosition(-1.0f, 0.0f, 3.0f); // Position the first cube
        CubeWorldTransform2.SetPosition(1.0f, 0.0f, 3.0f); // Initial position for the second cube
        TEST = 1;
    }
    CubeWorldTransform.Rotate(0.1f, 0.1f, 0.0f); // Rotate the first cube
    // No need to translate in this example, but you can add if desired

    // Set and use the first cube's WVP matrix
    Matrix4f World1 = CubeWorldTransform.GetMatrix();
    Matrix4f WVP1 = Projection * View * World1;
    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, &WVP1.m[0][0]);
    DrawCube(); // Assuming a function to encapsulate draw calls

    // Second Cube Transformations
    CubeWorldTransform2.Rotate(-0.1f, 0.1f, 0.0f); // Rotate the second cube differently
    // Apply other transformations to CubeWorldTransform2 as needed

    // Set and use the second cube's WVP matrix
    Matrix4f World2 = CubeWorldTransform2.GetMatrix();
    Matrix4f WVP2 = Projection * View * World2;
    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, &WVP2.m[0][0]);
    DrawCube(); 
    CubeWorldTransform.Translate(0, 0, 5*dx);
    glutPostRedisplay();
    glutSwapBuffers();
}


static void KeyboardCB(unsigned char key, int mouse_x, int mouse_y)
{
    GameCamera.OnKeyboard(key);
}

static void SpecialKeyboardCB(int key, int mouse_x, int mouse_y)
{
    GameCamera.OnKeyboard(key);
}

static void PassiveMouseCB(int x, int y)
{
    GameCamera.OnMouse(x, y);
}

static void MouseCB(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        GameCamera.OnMouseDown(button);
    } else if (state == GLUT_UP) {
        GameCamera.OnMouseUp(button);
    }
}

static void CreateVertexBuffer()
{
    VT Vertices[8];

    Vertices[0] = VT(0.1f, 0.1f, 0.1f);
    Vertices[1] = VT(-0.1f, 0.1f, -0.1f);
    Vertices[2] = VT(-0.1f, 0.1f, 0.1f);
    Vertices[3] = VT(0.1f, -0.1f, -0.1f);
    Vertices[4] = VT(-0.1f, -0.1f, -0.1f);
    Vertices[5] = VT(0.1f, 0.1f, -0.1f);
    Vertices[6] = VT(0.1f, -0.1f, 0.1f);
    Vertices[7] = VT(-0.1f, -0.1f, 0.1f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

static void CreateIndexBuffer()
{
    unsigned int Indices[] = {
                              0, 1, 2,
                              1, 3, 4,
                              5, 6, 3,
                              7, 3, 6,
                              2, 4, 7,
                              0, 7, 6,
                              0, 5, 1,
                              1, 5, 3,
                              5, 0, 6,
                              7, 4, 3,
                              2, 1, 4,
                              0, 2, 7
    };

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    int x = 200;
    int y = 100;
    glutInitWindowPosition(x, y);
    int win = glutCreateWindow("Tutorial 14");
    printf("window id: %d\n", win);

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    GLclampf Red = 0.2f, Green = 0.2f, Blue = 0.2f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    CreateVertexBuffer();
    CreateIndexBuffer();

    CompileShaders(VS_FILE_NAME, FS_FILE_NAME, gWVPLocation);

    glutDisplayFunc(RenderSceneCB);

    glutKeyboardFunc(KeyboardCB);
    glutSpecialFunc(SpecialKeyboardCB);
    glutMotionFunc(PassiveMouseCB);
    glutMouseFunc(MouseCB);
    glutMainLoop();

    return 0;
}
