
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

Camera GameCamera(WINDOW_WIDTH, WINDOW_HEIGHT, CAMERA_POS, CAMERA_TARGET, CAMERA_UP);

PersProjInfo persProjInfo = { FOV, WINDOW_WIDTH, WINDOW_HEIGHT, Z_NEAR, Z_FAR };

int TEST = 0;
static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);
    GameCamera.OnRender();
    float YRotationAngle = 0.1f;
    float dx = 0.001f;

    if (TEST ==0 ){
        CubeWorldTransform.SetPosition(0.0f, 0.0f, 2.0f);
        TEST = 1;
    }
    
    CubeWorldTransform.Rotate(0.0f, YRotationAngle, 0.0f);
    CubeWorldTransform.Translate(0, 0, 5*dx);
    //pose of object
    Matrix4f World = CubeWorldTransform.GetMatrix();
   
    Matrix4f View = GameCamera.GetMatrix();
    
    Matrix4f Projection;
    Projection.InitPersProjTransform(persProjInfo);

    Matrix4f WVP = Projection * View * World;

    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, &WVP.m[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

    // color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

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

struct Vertex {
    Vector3f pos;
    Vector3f color;

    Vertex() {}

    Vertex(float x, float y, float z)
    {
        pos = Vector3f(x, y, z);

        float red   = (float)rand() / (float)RAND_MAX;
        float green = (float)rand() / (float)RAND_MAX;
        float blue  = (float)rand() / (float)RAND_MAX;
        color = Vector3f(red, green, blue);
    }
};

static void CreateVertexBuffer()
{
    Vertex Vertices[8];

    Vertices[0] = Vertex(0.1f, 0.1f, 0.1f);
    Vertices[1] = Vertex(-0.1f, 0.1f, -0.1f);
    Vertices[2] = Vertex(-0.1f, 0.1f, 0.1f);
    Vertices[3] = Vertex(0.1f, -0.1f, -0.1f);
    Vertices[4] = Vertex(-0.1f, -0.1f, -0.1f);
    Vertices[5] = Vertex(0.1f, 0.1f, -0.1f);
    Vertices[6] = Vertex(0.1f, -0.1f, 0.1f);
    Vertices[7] = Vertex(-0.1f, -0.1f, 0.1f);

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
