#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>
#include "../ogl_utils/ogldev_math_3d.h" // Assuming this is where WorldTrans and Matrix4f are defined
#include "world_transform.h"
class Cube {
public:
    WorldTrans transform; // Transformation data for the cube

    Cube(const VT* vertices, unsigned int numVertices, const unsigned int* indices, unsigned int numIndices);
    ~Cube();
    
    void SetPosition(float x, float y, float z);
    void setRotation(float rx, float ry, float rz);
    void Draw(const Matrix4f& projection, const Matrix4f& view, GLuint gWVPLocation);

private:
    GLuint vbo; // Vertex Buffer Object
    GLuint ibo; // Index Buffer Object
    unsigned int numIndices; // Number of indices

    void createVertexBuffer(const VT* vertices, unsigned int numVertices);
    void createIndexBuffer(const unsigned int* indices, unsigned int numIndices);
};

#endif // CUBE_H
