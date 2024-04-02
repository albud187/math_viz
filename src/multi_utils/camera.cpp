

#include "camera.h"
#include "mesh.h"
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

    case 'W':
    case 'w':
    {
        m_up.Normalize();
        m_up *= m_speed;
        m_pos += m_up;
        break;

    }

    case 'S':
    case 's':
    {
        m_up.Normalize();
        m_up *= m_speed;
        m_pos -= m_up;
        break;
    }


    case 'D':
    case 'd':
    {
        Vector3f Right = m_up.Cross(m_target);
        Right.Normalize();
        Right *= m_speed;
        m_pos += Right;
        break;
    }


    case 'A':
    case 'a':
    {
        Vector3f Left = m_target.Cross(m_up);
        Left.Normalize();
        Left *= m_speed;
        m_pos += Left;
        break;
    }
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

Vector2f getNormalizedDeviceCoords(int mouseX, int mouseY, int screenWidth, int screenHeight) {
    float x = (2.0f * mouseX) / screenWidth - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / screenHeight;
    return Vector2f(x, y);
}

Vector4f getHomogeneousClipCoords(Vector2f ndc) {
    return Vector4f(ndc.x, ndc.y, -1.0f, 1.0f);
}


Vector4f toEyeCoords(Vector4f clipCoords, Matrix4f projectionMatrix) {
    Matrix4f invProjection = projectionMatrix.Inverse();
    Vector4f eyeCoords = invProjection * clipCoords;
    return Vector4f(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
}

Vector3f toWorldCoords(Vector4f eyeCoords, Matrix4f viewMatrix) {
    Matrix4f invView = viewMatrix.Inverse();
    Vector4f rayWorld = invView * eyeCoords;
    Vector3f mouseRay = Vector3f(rayWorld.x, rayWorld.y, rayWorld.z);
    mouseRay = mouseRay.Normalize();
    return mouseRay;
}

Vector3f cameraRay(int mouseX, int mouseY, int screenWidth, int screenHeight, Matrix4f projectionMatrix, Matrix4f viewMatrix){
    float x = (2.0f * mouseX) / screenWidth - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / screenHeight;
    Vector4f clipCoords = Vector4f(x,y,-1.0,1.0);
    Matrix4f invProjection = projectionMatrix.Inverse();
    Vector4f eyeCoords = invProjection * clipCoords;
    
    Matrix4f invView = viewMatrix.Inverse();
    Vector4f rayWorld = invView * eyeCoords;
    Vector3f mouseRay = Vector3f(rayWorld.x, rayWorld.y, rayWorld.z);
    mouseRay = mouseRay.Normalize();
    return mouseRay;
}

// Mesh* rayIntersectTest(std::vector<std::shared_ptr<Mesh>> game_objects, Vector3f camera_ray){

    
//     Mesh* closestMesh = nullptr;
//     for (const auto& mesh: game_objects){

//     }
// }

//orig = camera location
//dir = camray
//v0, v1, v2 are verticies
//t = distance
//u = 

// bool ray_intersects_triangle(vec3 ray_origin, 
//                              vec3 ray_vector, 
//                              const triangle3& triangle,
//                              vec3& out_intersection_point)
// {
//     constexpr float epsilon = std::numeric_limits<float>::epsilon();

//     vec3 edge1 = triangle.b - triangle.a;
//     vec3 edge2 = triangle.c - triangle.a;
//     vec3 ray_cross_e2 = cross(ray_vector, edge2);
//     float det = dot(edge1, ray_cross_e2);

//     if (det > -epsilon && det < epsilon)
//         return false;    // This ray is parallel to this triangle.

//     float inv_det = 1.0 / det;
//     vec3 s = ray_origin - triangle.a;
//     float u = inv_det * dot(s, ray_cross_e2);

//     if (u < 0 || u > 1)
//         return false;

//     vec3 s_cross_e1 = cross(s, edge1);
//     float v = inv_det * dot(ray_vector, s_cross_e1);

//     if (v < 0 || u + v > 1)
//         return false;

//     // At this stage we can compute t to find out where the intersection point is on the line.
//     float t = inv_det * dot(edge2, s_cross_e1);

//     if (t > epsilon) // ray intersection
//     {
//         out_intersection_point = ray_origin + ray_vector * t;
//         return true;
//     }
//     else // This means that there is a line intersection but not a ray intersection.
//         return false;
// }