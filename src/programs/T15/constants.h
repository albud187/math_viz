
#include "../../ogl_utils/ogldev_math_3d.h"

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

#endif