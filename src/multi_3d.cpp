
#include <stdio.h>
#include <string.h>

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ogl_utils/ogldev_math_3d.h"
#include "multi_utils/camera.h"
#include "multi_utils/world_transform.h"
#include "multi_utils/constants.h"
#include "multi_utils/shaders.h"

GLuint VBO;
GLuint IBO;
GLuint gWVPLocation;

WorldTrans CubeWorldTransform;

WorldTrans CubeWorldTransform2;
Camera GameCamera(WINDOW_WIDTH, WINDOW_HEIGHT, CAMERA_POS, CAMERA_TARGET, CAMERA_UP);

PersProjInfo persProjInfo = { FOV, WINDOW_WIDTH, WINDOW_HEIGHT, Z_NEAR, Z_FAR };

int TEST =0;
static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);
    GameCamera.OnRender();
    float YRotationAngle = 0.1f;
    float dx = 0.001f;

    if (TEST ==0 ){
        CubeWorldTransform.SetPosition(0.0f, 0.0f, 2.0f);
        CubeWorldTransform2.SetPosition(0.0f, 2.0f, 0.0f);
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
