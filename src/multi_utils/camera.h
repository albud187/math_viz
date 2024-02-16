
#ifndef CAMERA_H
#define CAMERA_H

#include "../ogl_utils/ogldev_math_3d.h"
class Camera
{
public:

    Camera(int WindowWidth, int WindowHeight);

    Camera(int WindowWidth, int WindowHeight, const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up);

    void SetPosition(float x, float y, float z);

    void OnKeyboard(unsigned char key);

    void OnMouseDown(int button, int x, int y);
    void OnMouseUp(int button);
    void OnMouse(int x, int y);

    void OnRender();

    Matrix4f GetMatrix();
    bool m_LeftButtonDown = false;
    int X0;
    int Y0;
private:

    int CHECK;
    
    void Init();
    void Update();

    Vector3f m_pos;
    Vector3f m_target;
    Vector3f m_up;
    float m_speed = 1.0f;

    int m_windowWidth;
    int m_windowHeight;

    float m_AngleH;
    float m_AngleV;

    bool m_OnUpperEdge;
    bool m_OnLowerEdge;
    bool m_OnLeftEdge;
    bool m_OnRightEdge;

    Vector2i m_mousePos;
};

#endif  /* CAMERA_H */
