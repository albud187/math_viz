

#include "camera.h"
#include <GL/freeglut.h>
#include <iostream>
static int MARGIN = 10;
static float EDGE_STEP = 1.0f;

Camera::Camera(int WindowWidth, int WindowHeight)
{
    m_windowWidth  = WindowWidth;
    m_windowHeight = WindowHeight;
    m_pos          = Vector3f(0.0f, 0.0f, 0.0f);
    m_target       = Vector3f(0.0f, 0.0f, 1.0f);
    m_up           = Vector3f(0.0f, 1.0f, 0.0f);

    Init();
}


Camera::Camera(int WindowWidth, int WindowHeight, const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up)
{
    m_windowWidth  = WindowWidth;
    m_windowHeight = WindowHeight;
    m_pos = Pos;

    m_target = Target;
    m_target.Normalize();

    m_up = Up;
    m_up.Normalize();

    Init();
}


void Camera::Init()
{
    Vector3f HTarget(m_target.x, 0.0, m_target.z);
    HTarget.Normalize();

    float Angle = ToDegree(asin(abs(HTarget.z)));

    if (HTarget.z >= 0.0f)
    {
        if (HTarget.x >= 0.0f)
        {
            m_AngleH = 360.0f - Angle;
        }
        else
        {
            m_AngleH = 180.0f + Angle;
        }
    }
    else
    {
        if (HTarget.x >= 0.0f)
        {
            m_AngleH = Angle;
        }
        else
        {
            m_AngleH = 180.0f - Angle;
        }
    }

    m_AngleV = -ToDegree(asin(m_target.y));

    m_OnUpperEdge = false;
    m_OnLowerEdge = false;
    m_OnLeftEdge  = false;
    m_OnRightEdge = false;
    m_mousePos.x  = m_windowWidth / 2;
    m_mousePos.y  = m_windowHeight / 2;
}


void Camera::SetPosition(float x, float y, float z)
{
    m_pos.x = x;
    m_pos.y = y;
    m_pos.z = z;
}


void Camera::OnKeyboard(unsigned char Key)
{
    std::cout<<Key<<std::endl;
    switch (Key) {

    case 'Q':
    case 'q':
        m_pos.y += m_speed;
        break;
    case 'Z':
    case 'z':
        m_pos.y -= m_speed;
        break;

    case 'W':
    case 'w':
        m_pos.z += m_speed;
        break;

    case 'S':
    case 's':
        m_pos.z -= m_speed;
        break;

    case 'D':
    case 'd':
        m_pos.x += m_speed;
        break;

    case 'A':
    case 'a':
        m_pos.x -= m_speed;
        break;

    case '+':
    case '=':
        m_speed += 0.1f;
        printf("Speed changed to %f\n", m_speed);
        break;

    case '-':
        m_speed -= 0.1f;
        if (m_speed < 0.1f) {
            m_speed = 0.1f;
        }
        printf("Speed changed to %f\n", m_speed);
        break;
    }
}


void Camera::OnMouseDown(int button, int x, int y) {
    std::cout<<button<<std::endl;
    switch (button) {
    case 0:
        m_LeftButtonDown = true;
        X0 = x;
        Y0 = y;
        break;
    case 3:
        m_pos += (m_target * m_speed);
        break;
    case 4:
        m_pos -= (m_target * m_speed);
        break;
    }



}
void Camera::OnMouseUp(int button) {
   
    m_LeftButtonDown = false;
   
}

void Camera::OnMouse(int x, int y) {
    if (m_LeftButtonDown) {
        int DeltaX = x - X0;
        int DeltaY = y - Y0;
        
        m_AngleH += (float)DeltaX / 200.0f;
        m_AngleV += (float)DeltaY / 500.0f;

        m_AngleH = fmod(m_AngleH, 360.0f);
        if (m_AngleH < 0) m_AngleH += 360.0f; 

        m_AngleV = fmod(m_AngleV, 360.0f);
        if (m_AngleV < 0) m_AngleV += 360.0f;

        Update();
    }
}

void Camera::OnRender()
{
    bool ShouldUpdate = false;

    if (m_OnLeftEdge) {
        m_AngleH -= EDGE_STEP;
        ShouldUpdate = true;
    }
    else if (m_OnRightEdge) {
        m_AngleH += EDGE_STEP;
        ShouldUpdate = true;
    }

    if (m_OnUpperEdge) {
        if (m_AngleV > -90.0f) {
            m_AngleV -= EDGE_STEP;
            ShouldUpdate = true;
        }
    }
    else if (m_OnLowerEdge) {
        if (m_AngleV < 90.0f) {
           m_AngleV += EDGE_STEP;
           ShouldUpdate = true;
        }
    }

    if (ShouldUpdate) {
        Update();

   
    }
}

void Camera::Update()
{
    Vector3f Yaxis(0.0f, 1.0f, 0.0f);

    // Rotate the view vector by the horizontal angle around the vertical axis
    Vector3f View(1.0f, 0.0f, 0.0f);
    View.Rotate(m_AngleH, Yaxis);
    View.Normalize();

    // Rotate the view vector by the vertical angle around the horizontal axis
    Vector3f U = Yaxis.Cross(View);
    U.Normalize();
    View.Rotate(m_AngleV, U);

    m_target = View;
    m_target.Normalize();

    m_up = m_target.Cross(U);
    m_up.Normalize();

}



Matrix4f Camera::GetMatrix()
{
    Matrix4f CameraTransformation;
    CameraTransformation.InitCameraTransform(m_pos, m_target, m_up);

    return CameraTransformation;
}