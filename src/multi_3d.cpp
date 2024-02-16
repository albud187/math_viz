
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <unordered_map>
#include <memory>
#include <algorithm>
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

std::vector<std::shared_ptr<Mesh>> game_objects;

void init_game_objects() {
    auto cube1 = std::make_shared<Mesh>(PYRAMID3_VERTICES, n_v_pyramid3, PYRAMID3_INDICES, n_i_pyramid3);
    auto cube2 = std::make_shared<Mesh>(PYRAMID3_VERTICES, n_v_pyramid3, PYRAMID3_INDICES, n_i_pyramid3);
    auto cube3 = std::make_shared<Mesh>(PYRAMID3_VERTICES, n_v_pyramid3, PYRAMID3_INDICES, n_i_pyramid3);
    
    cube1->SetPosition(-1.0f, 0.0f, 3.0f);
    cube2->SetPosition(1.0f, 0.0f, 3.0f);
    cube3->SetPosition(2.0f, 0.0f, 3.0f);

    cube1->setRotation(0, 0, 5);
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

    GameCamera.OnRender();
    Matrix4f Projection;
    Matrix4f View = GameCamera.GetMatrix();
    Projection.InitPersProjTransform(persProjInfo);

    draw_all(game_objects, Projection, View, gWVPLocation);

    for (auto &game_obj : game_objects){
        game_obj->rotate(0.25,0.0,0.0);
    }

    glutPostRedisplay();
    glutSwapBuffers();
}

float pos = 0;
static void spawn_object(){
  
    //auto c_obj = std::make_shared<Mesh>(PYRAMID3_VERTICES, n_v_pyramid3, PYRAMID3_INDICES, n_i_pyramid3);
 
    auto c_obj = std::make_shared<Mesh>(CUBE_VERTICES, n_v_cube, CUBE_INDICES, n_i_cube);

    c_obj->SetPosition(pos,pos,pos);
    c_obj->setRotation(-20,50,90);
    game_objects.push_back(c_obj);
    pos = pos+2;
}


static void KeyboardCB(unsigned char key, int mouse_x, int mouse_y)
{
    std::cout<<key<<std::endl;
    if (std::find(CAM_KEYS.begin(), CAM_KEYS.end(), key)!=CAM_KEYS.end()){
        GameCamera.OnKeyboard(key);
    }
    if (std::find(WORK_KEYS.begin(), WORK_KEYS.end(), key)!=WORK_KEYS.end()){
        spawn_object();
    }

   
}

static void SpecialKeyboardCB(int key, int mouse_x, int mouse_y)
{
    GameCamera.OnKeyboard(key);
   
}

static void MotionCB(int x, int y) {
    GameCamera.OnMouse(x, y);
}

static void MouseCB(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        GameCamera.OnMouseDown(button, x, y); // Pass x and y coordinates
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
    //glutSpecialFunc(SpecialKeyboardCB);
    
    glutMouseFunc(MouseCB);
    glutMotionFunc(MotionCB);
    glutMouseFunc(MouseCB);
    glutMainLoop();

    return 0;
}
