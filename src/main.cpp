#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <chrono>
#include <thread>
#include "ogl_utils/ogldev_math_3d.h"
#include "multi_utils/camera.h"
#include "multi_utils/world_transform.h"
#include "multi_utils/constants.h"
#include "multi_utils/shaders.h"
#include "multi_utils/mesh.h"

GLuint gWVPLocation;
Camera GameCamera(WINDOW_WIDTH, WINDOW_HEIGHT, CAMERA_POS, CAMERA_TARGET, CAMERA_UP);
PersProjInfo persProjInfo = { FOV, WINDOW_WIDTH, WINDOW_HEIGHT, Z_NEAR, Z_FAR };

std::vector<std::shared_ptr<Mesh>> game_objects;
std::vector<GLuint> shaders; 
std::vector<std::shared_ptr<Mesh>> grid_objects;
std::shared_ptr<Mesh> target_object = nullptr;
GLuint pickingFramebuffer = 0;
GLuint pickingTexture = 0;

void initPickingFramebuffer() {
    glGenFramebuffers(1, &pickingFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, pickingFramebuffer);

    glGenTextures(1, &pickingTexture);
    glBindTexture(GL_TEXTURE_2D, pickingTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pickingTexture, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "Framebuffer not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void init_shaders(){
    GLuint shader1 = CompileShaders(VS_FILE_NAME, FS_FILE_NAME);
    GLuint shader2 = CompileShaders(VS2_FILE_NAME, FS2_FILE_NAME);
    shaders.push_back(shader1);
    shaders.push_back(shader2);
}

void init_game_objects() {

    auto s1 = std::make_shared<Mesh>(PYRAMID3_VERTICES, NV_PYRAMID3, PYRAMID3_INDICES, NI_PYRAMID3);
    s1->SetShaderProgram(shaders[0]);
    s1->setID(11);
    s1->SetPosition(0, 0, 0);
    s1->setRotation(0, 0, 0);
    game_objects.push_back(s1);

    // auto s2 = std::make_shared<Mesh>(PYRAMID3_VERTICES, NV_PYRAMID3, PYRAMID3_INDICES, NI_PYRAMID3);
    // s2->SetShaderProgram(shaders[0]);
    // s2->setID(22);
    // s2->SetPosition(1.0f, 1.0f, 3.0f);
    // s2->setRotation(0, 0, 0);
    // game_objects.push_back(s2);

    // auto s3 = std::make_shared<Mesh>(PYRAMID3_VERTICES, NV_PYRAMID3, PYRAMID3_INDICES, NI_PYRAMID3);
    // s3->SetShaderProgram(shaders[0]);
    // s3->setID(33);
    // s3->SetPosition(2.0f, 1.0f, 3.0f);
    // s3->setRotation(0, 0, 0);
    // game_objects.push_back(s3);

    for (int k = 0; k<GRID_L; k++){
        for (int i = 0; i<GRID_W; i++){
            auto grid_square = std::make_shared<Mesh>(SQUARE_VERTICES, NV_SQ, SQUARE_INDICES, NI_SQ);
            grid_square->SetShaderProgram(shaders[0]);
            grid_square->SetPosition(k-GRID_L/2, 0, i-GRID_W/2);
            grid_square->setRotation(0,0,0);
            grid_objects.push_back(grid_square);
        }
    }
}

static void RenderSceneCB()
{

    static auto lastFrameTime = std::chrono::high_resolution_clock::now();
    auto startFrameTime = std::chrono::high_resolution_clock::now();
    //picking phase
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    GameCamera.OnRender();
    Matrix4f Projection;
    Matrix4f View = GameCamera.GetMatrix();
    Projection.InitPersProjTransform(persProjInfo);

    draw_triangles(game_objects, Projection, View, gWVPLocation);
    draw_lines(grid_objects, Projection, View, gWVPLocation);
    
    game_objects[0]->Draw(Projection, View, gWVPLocation);
   
 
    glutPostRedisplay();
    glutSwapBuffers();

    auto endFrameTime = std::chrono::high_resolution_clock::now();
    auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endFrameTime - startFrameTime);
    auto targetFrameTime = std::chrono::milliseconds(TARGET_FPS_DELAY_MS);

    if (frameDuration < targetFrameTime) {
        auto sleepDuration = targetFrameTime - frameDuration;
        std::this_thread::sleep_for(targetFrameTime - frameDuration);
    }
    lastFrameTime = std::chrono::high_resolution_clock::now();
    
}

float pos_y = 0;
static void spawn_object(){

    auto c_obj = std::make_shared<Mesh>(CUBE_VERTICES, NV_CUBE, CUBE_INDICES, NI_CUBE);
       
    c_obj->SetShaderProgram(shaders[0]);
    c_obj->SetPosition(0,pos_y,0);
    c_obj->setRotation(0,0,0);
    game_objects.push_back(c_obj);
    pos_y = pos_y+1;
}

static void KeyboardCB(unsigned char key, int mouse_x, int mouse_y)
{
    if (std::find(CAM_KEYS.begin(), CAM_KEYS.end(), key)!=CAM_KEYS.end()){
        GameCamera.OnKeyboard(key);
    }
    if (std::find(WORK_KEYS.begin(), WORK_KEYS.end(), key)!=WORK_KEYS.end()){
        spawn_object();
    }
    
    if(std::find(MESH_MOVE_KEYS.begin(), MESH_MOVE_KEYS.end(), key)!=MESH_MOVE_KEYS.end()){
        if (target_object!=nullptr){
            move_mesh(target_object, key);
        }
    }
}
static void MotionCB(int x, int y) {
    GameCamera.OnMouse(x, y);
}
static void MouseCB(int button, int state, int x, int y) {
    
    Matrix4f Projection;
    Projection.InitPersProjTransform(persProjInfo);
    Matrix4f ViewMat = GameCamera.GetMatrix();

    if (state == GLUT_DOWN) {
        if (button == 0 ){
            Vector3f cam_ray = cameraRay(x, y, WINDOW_WIDTH, WINDOW_HEIGHT, Projection, ViewMat);
            Vector3f cam_pos = Vector3f(GameCamera.m_pos.x, GameCamera.m_pos.y, GameCamera.m_pos.z);
            std::vector<std::pair<std::shared_ptr<Mesh>, float>> all_intersections = ObjectDistances(game_objects, cam_ray, cam_pos);
            std::shared_ptr<Mesh> picked_object = pick_object(all_intersections);
            if (picked_object != nullptr){
                target_object = picked_object;
                std::cout<<"object picked with ID: "<<target_object->obj_id<<std::endl;
            }
        }
        GameCamera.OnMouseDown(button, x, y); 
    } else if (state == GLUT_UP) {
        GameCamera.OnMouseUp(button);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    glutInitWindowPosition(0, 0);
    int win = glutCreateWindow("Multi 3D");
    printf("window id: %d\n", win);

    GLenum res = glewInit();

    GLclampf Red = 0.025f, Green = 0.025f, Blue = 0.025f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);

    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glDepthFunc(GL_LESS); // Specify depth comparison functio
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    init_shaders();
    glutDisplayFunc(RenderSceneCB);
    init_game_objects();
    
    glutKeyboardFunc(KeyboardCB);
    glutMouseFunc(MouseCB);
    glutMotionFunc(MotionCB);
    glutMainLoop();

    return 0;
}