#ifndef WORLD_TRANSFORM_H
#define WORLD_TRANSFORM_H

#include "../../ogl_utils/ogldev_math_3d.h"

class WorldTrans {
 public:
    WorldTrans() {}

    void SetScale(float scale);
    void SetRotation(float x, float y, float z);
    void SetPosition(float x, float y, float z);
    void Translate(float x, float y, float z);
    void Rotate(float x, float y, float z);

    Matrix4f GetMatrix();

 private:
    float    m_scale    = 1.0f;
    Vector3f m_rotation = Vector3f(0.0f, 0.0f, 0.0f);
    Vector3f m_pos      = Vector3f(0.0f, 0.0f, 0.0f);
};
struct VT {
    Vector3f pos;
    Vector3f color;

    VT(); // Default constructor
    VT(float x, float y, float z); // Parameterized constructor
};

#endif
