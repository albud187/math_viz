
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <unordered_map>
#include <memory>
#include "ogl_utils/ogldev_math_3d.h"
#include "multi_utils/camera.h"
#include "multi_utils/world_transform.h"
#include "multi_utils/constants.h"
#include "multi_utils/shaders.h"
#include "multi_utils/mesh.h"

GLuint VBO;
GLuint IBO;
GLuint gWVPLocation;



Camera GameCamera(WINDOW_WIDTH, WINDOW_HEIGHT, CAMERA_POS, CAMERA_TARGET, CAMERA_UP);

PersProjInfo persProjInfo = { FOV, WINDOW_WIDTH, WINDOW_HEIGHT, Z_NEAR, Z_FAR };

//std::unordered_map<std::string, Mesh> game_objects;
std::vector<std::shared_ptr<Mesh>> game_objects;

void init_game_objects() {
    auto cube1 = std::make_shared<Mesh>(PYRAMID3_VERTICES, n_v_pyramid3, PYRAMID3_INDICES, n_i_pyramid3);
    auto cube2 = std::make_shared<Mesh>(PYRAMID3_VERTICES, n_v_pyramid3, PYRAMID3_INDICES, n_i_pyramid3);
    auto cube3 = std::make_shared<Mesh>(PYRAMID3_VERTICES, n_v_pyramid3, PYRAMID3_INDICES, n_i_pyramid3);
    // Set positions and rotations
    cube1->SetPosition(-1.0f, 0.0f, 3.0f);
    cube2->SetPosition(1.0f, 0.0f, 3.0f);
    cube3->SetPosition(2.0f, 0.0f, 3.0f);

    cube1->setRotation(0, 0, 5.0f);
    cube2->setRotation(0, 0, 5.0f);
    cube3->setRotation(0, 0, 5.0f);

    game_objects.push_back(cube1);
    game_objects.push_back(cube2);
    game_objects.push_back(cube3);
}
float x = 0;
static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

    // Camera setup
    GameCamera.OnRender();
    Matrix4f Projection;
    Matrix4f View = GameCamera.GetMatrix();
    Projection.InitPersProjTransform(persProjInfo);
    // auto c4 = std::make_shared<Mesh>(PYRAMID3_VERTICES, n_v_pyramid3, PYRAMID3_INDICES, n_i_pyramid3);
    // c4->SetPosition(5.0f, 0.0f, 3.0f);
    // c4->setRotation(0, 200, 5.0f);
    // game_objects.push_back(c4);
    // x = x+1;
    game_objects[0]->setRotation(x,0,0);
    draw_all(game_objects, Projection, View, gWVPLocation);

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
    init_game_objects();
    glutKeyboardFunc(KeyboardCB);
    glutSpecialFunc(SpecialKeyboardCB);
    glutMotionFunc(PassiveMouseCB);
    glutMouseFunc(MouseCB);
    glutMainLoop();

    return 0;
}
