#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>
#include "../ogl_utils/ogldev_math_3d.h" 
#include "world_transform.h"
class Mesh {
public:
    WorldTrans transform; // Transformation data for the mesh

    Mesh(const VT* vertices, unsigned int numVertices, const unsigned int* indices, unsigned int numIndices);
    ~Mesh();
    
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
