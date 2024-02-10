#include "game_object.h"
#include <iostream>

void GameObject::SetScale(float scale)
{
    m_scale = scale;
}

void GameObject::SetRotation(float x, float y, float z)
{
    m_rotation.x = x;
    m_rotation.y = y;
    m_rotation.z = z;
}

void GameObject::SetPosition(float x, float y, float z)
{
    m_pos.x = x;
    m_pos.y = y;
    m_pos.z = z;
}

void GameObject::Rotate(float x, float y, float z)
{
    m_rotation.x += x;
    m_rotation.y += y;
    m_rotation.z += z;
}

void GameObject::Translate(float x, float y, float z)
{
    m_pos.x += x;
    m_pos.y += y;
    m_pos.z += z;
}

Matrix4f GameObject::GetMatrix()
{
    Matrix4f Scale;
    Scale.InitScaleTransform(m_scale, m_scale, m_scale);

    Matrix4f Rotation;
    Rotation.InitRotateTransform(m_rotation.x, m_rotation.y, m_rotation.z);

    Matrix4f Translation;
    Translation.InitTranslationTransform(m_pos.x, m_pos.y, m_pos.z);

    Matrix4f GameObjectformation = Translation * Rotation * Scale;

    return GameObjectformation;
}
