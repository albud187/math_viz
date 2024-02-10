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
    std::cout<<m_pos.x<<std::endl;
    std::cout<<m_pos.y<<std::endl;
    std::cout<<m_pos.z<<std::endl;
    std::cout<<" "<<std::endl;
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
