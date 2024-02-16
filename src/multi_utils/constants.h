
#include "../ogl_utils/ogldev_math_3d.h"
#include "world_transform.h"
#ifndef CONSTANTS_H
#define CONSTANTS_H

float WINDOW_WIDTH = 1500;
float WINDOW_HEIGHT = 900;

Vector3f CAMERA_POS(1.0f, 1.0f, 0.0f);
Vector3f CAMERA_TARGET(0.0f, 0.0f, 1.0f);
Vector3f CAMERA_UP(0.0f, 1.0f, 0.0f);

float FOV = 45.0f;
float Z_NEAR= 0.25f;
float Z_FAR = 1000.0f;

const char* VS_FILE_NAME= "/home/alfab/experiments/math_viz/src/shaders/T15/shader.vs";
const char* FS_FILE_NAME = "/home/alfab/experiments/math_viz/src/shaders/T15/shader.fs";

unsigned int CUBE_INDICES[] = {
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
VT CUBE_VERTICES[8] = {
    VT(0.1f, 0.1f, 0.1f),
    VT(-0.1f, 0.1f, -0.1f),
    VT(-0.1f, 0.1f, 0.1f),
    VT(0.1f, -0.1f, -0.1f),
    VT(-0.1f, -0.1f, -0.1f),
    VT(0.1f, 0.1f, -0.1f),
    VT(0.1f, -0.1f, 0.1f),
    VT(-0.1f, -0.1f, 0.1f)
    };

// Define the vertices for a triangular-based pyramid
VT PYRAMID3_VERTICES[] = {
    VT(0.0f, 0.5f, 0.0f),    // Tip of the pyramid
    VT(-0.5f, -0.5f, 0.5f),  // Base vertex 1
    VT(0.5f, -0.5f, 0.5f),   // Base vertex 2
    VT(0.0f, -0.5f, -0.7f)   // Base vertex 3
};

// Define the indices for the faces of the pyramid
unsigned int PYRAMID3_INDICES[] = {
    0, 1, 2,  // Side 1
    0, 2, 3,  // Side 2
    0, 3, 1,  // Side 3
    1, 3, 2   // Base
};

unsigned int n_v_pyramid3 = sizeof(PYRAMID3_VERTICES) / sizeof(PYRAMID3_VERTICES[0]);
unsigned int n_i_pyramid3 = sizeof(PYRAMID3_INDICES) / sizeof(PYRAMID3_INDICES[0]);
#endif