
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <unordered_map>
#include "ogl_utils/ogldev_math_3d.h"
#include "multi_utils/camera.h"
#include "multi_utils/world_transform.h"
#include "multi_utils/constants.h"
#include "multi_utils/shaders.h"
#include "multi_utils/mesh.h"

GLuint VBO;
GLuint IBO;
GLuint gWVPLocation;

unsigned int n_v_pyramid3 = sizeof(PYRAMID3_VERTICES) / sizeof(PYRAMID3_VERTICES[0]);
unsigned int n_i_pyramid3 = sizeof(PYRAMID3_INDICES) / sizeof(PYRAMID3_INDICES[0]);

Camera GameCamera(WINDOW_WIDTH, WINDOW_HEIGHT, CAMERA_POS, CAMERA_TARGET, CAMERA_UP);

PersProjInfo persProjInfo = { FOV, WINDOW_WIDTH, WINDOW_HEIGHT, Z_NEAR, Z_FAR };

std::unordered_map<std::string, Mesh> game_objects;

// Global or static rotation angles
static float rotationAngle1 = 0.0f;
static float rotationAngle2 = 0.0f;
static float rotationAngle3 = 0.0f;
static float px = -1.0f;

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

    // Camera setup
    GameCamera.OnRender();
    Matrix4f Projection;
    Matrix4f View = GameCamera.GetMatrix();
    Projection.InitPersProjTransform(persProjInfo);

    Mesh cube1(PYRAMID3_VERTICES, n_v_pyramid3, PYRAMID3_INDICES, n_i_pyramid3);
    Mesh cube2(PYRAMID3_VERTICES, n_v_pyramid3, PYRAMID3_INDICES, n_i_pyramid3);
    Mesh cube3(PYRAMID3_VERTICES, n_v_pyramid3, PYRAMID3_INDICES, n_i_pyramid3);

    // Set initial positions (could be moved outside and made static if they don't change)
    cube1.SetPosition(-1.0f, 0.0f, 3.0f);
    cube2.SetPosition(1.0f, 0.0f, 3.0f);
    cube3.SetPosition(2.0f, 0.0f, 3.0f);
    
    // Increment rotation angles
    rotationAngle1 += 0.05f;
    rotationAngle2 += 0.10f;
    rotationAngle3 += 0.20f;

    // Apply rotations
    cube1.setRotation(rotationAngle1, rotationAngle1, 5.0f);
    cube2.setRotation(rotationAngle2, rotationAngle2, 5.0f);
    cube3.setRotation(rotationAngle3, rotationAngle3, 5.0f);

    // Draw cubes
    cube1.Draw(Projection, View, gWVPLocation);
    cube2.Draw(Projection, View, gWVPLocation);
    cube3.Draw(Projection, View, gWVPLocation);

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


    CompileShaders(VS_FILE_NAME, FS_FILE_NAME, gWVPLocation);

    glutDisplayFunc(RenderSceneCB);

    glutKeyboardFunc(KeyboardCB);
    glutSpecialFunc(SpecialKeyboardCB);
    glutMotionFunc(PassiveMouseCB);
    glutMouseFunc(MouseCB);
    glutMainLoop();

    return 0;
}
