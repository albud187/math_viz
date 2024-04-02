
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


Vector2f getNormalizedDeviceCoords(int mouseX, int mouseY, int screenWidth, int screenHeight);

Vector4f getHomogeneousClipCoords(Vector2f ndc);

Vector4f toEyeCoords(Vector4f clipCoords, Matrix4f projectionMatrix);

Vector3f toWorldCoords(Vector4f eyeCoords, Matrix4f viewMatrix);

Vector3f cameraRay(int mouseX, int mouseY, int screenWidth, int screenHeight, Matrix4f projectionMatrix, Matrix4f viewMatrix);

// Mesh* rayIntersectTest(std::vector<std::shared_ptr<Mesh>> game_objects, Vector3f camera_ray);

#endif  
