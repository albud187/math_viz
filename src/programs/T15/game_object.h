#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../../ogl_utils/ogldev_math_3d.h"

class GameObject {
 public:
    GameObject() {}

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


#endif
