#include "world_transform.h"
#include <iostream>

void WorldTrans::SetScale(float scale)
{
    m_scale = scale;
}


void WorldTrans::SetRotation(float x, float y, float z)
{
    m_rotation.x = x;
    m_rotation.y = y;
    m_rotation.z = z;
}


void WorldTrans::SetPosition(float x, float y, float z)
{
    m_pos.x = x;
    m_pos.y = y;
    m_pos.z = z;
}

void WorldTrans::Rotate(float x, float y, float z)
{
    m_rotation.x += x;
    m_rotation.y += y;
    m_rotation.z += z;
}

void WorldTrans::Translate(float x, float y, float z)
{
    m_pos.x += x;
    m_pos.y += y;
    m_pos.z += z;
}
Matrix4f WorldTrans::GetMatrix()
{
    Matrix4f Scale;
    Scale.InitScaleTransform(m_scale, m_scale, m_scale);

    Matrix4f Rotation;
    Rotation.InitRotateTransform(m_rotation.x, m_rotation.y, m_rotation.z);

    Matrix4f Translation;
    Translation.InitTranslationTransform(m_pos.x, m_pos.y, m_pos.z);

    Matrix4f WorldTransformation = Translation * Rotation * Scale;

    return WorldTransformation;
}

VT::VT () {

}

VT::VT(float x, float y, float z) {
    pos = Vector3f(x, y, z);

    float red   = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float green = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float blue  = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    color = Vector3f(red, green, blue);
}