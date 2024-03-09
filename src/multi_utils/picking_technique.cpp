

#include "picking_technique.h"
#include "../ogl_utils/ogldev_util.h"

PickingTechnique::PickingTechnique()
{   
}

bool PickingTechnique::Init()
{
    if (!Technique::Init()) {
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER, "picking.vs")) {
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, "picking.fs")) {
        return false;
    }
    
    if (!Finalize()) {
        return false;
    }

    m_WVPLocation = GetUniformLocation("gWVP");
    m_objectIndexLocation = GetUniformLocation("gObjectIndex");
    m_drawIndexLocation = GetUniformLocation("gDrawIndex");

    if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
        m_objectIndexLocation == INVALID_UNIFORM_LOCATION ||
        m_drawIndexLocation == INVALID_UNIFORM_LOCATION) {
        return false;
    }

    return true;
}


void PickingTechnique::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);    
}


void PickingTechnique::DrawStartCB(uint DrawIndex)
{
    glUniform1ui(m_drawIndexLocation, DrawIndex);
}


void PickingTechnique::SetObjectIndex(uint ObjectIndex)
{
    GLExitIfError;
    glUniform1ui(m_objectIndexLocation, ObjectIndex);
//    GLExitIfError;
}