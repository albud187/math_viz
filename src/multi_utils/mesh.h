#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "../ogl_utils/ogldev_math_3d.h" 
#include "world_transform.h"
#include <memory>

class Mesh {
public:
    WorldTrans transform; // Transformation data for the mesh
    GLuint shaderProgramID;
    Vector3f uniqueColor;
    int obj_id;
    Mesh(const VT* vertices, unsigned int numVertices, const unsigned int* indices, unsigned int numIndices);
    ~Mesh();
    
    void SetPosition(float x, float y, float z);
    void setRotation(float rx, float ry, float rz);
    void translate(float x, float y, float z);
    void rotate(float rx, float ry, float rz);
    void Draw(const Matrix4f& projection, const Matrix4f& view, GLuint gWVPLocation);
    void DrawLine(const Matrix4f& projection, const Matrix4f& view, GLuint gWVPLocation);
    void SetShaderProgram(GLuint programID);
    void setID(int id_num);
private:
    GLuint vbo; // Vertex Buffer Object
    GLuint ibo; // Index Buffer Object
    unsigned int numIndices; // Number of indices
   
    void createVertexBuffer(const VT* vertices, unsigned int numVertices);
    void createIndexBuffer(const unsigned int* indices, unsigned int numIndices);
    
};

void draw_triangles(const std::vector<std::shared_ptr<Mesh>>& game_objects, Matrix4f Projection, Matrix4f View, GLuint gWVPLocation);
void draw_lines(const std::vector<std::shared_ptr<Mesh>>& game_objects, Matrix4f Projection, Matrix4f View, GLuint gWVPLocation);

VT* generateSquareVertices(float sideLength);

unsigned int* generateSquareIndices();

void move_mesh(std::shared_ptr<Mesh> mesh_ptr, unsigned char key);

void printTrianglePoint(Vector3f p);

struct meshTriangle {
    Vector3f a;
    Vector3f b;
    Vector3f c;
    meshTriangle(Vector3f p1, Vector3f p2, Vector3f p3);

};

std::vector<meshTriangle> get3DTriangle(VT* verticies, WorldTrans transform, int size);
std::vector<meshTriangle> get3DTriangles(VT* verticies, unsigned int* indices, int n_indices, WorldTrans transform);

bool intersectTest(Vector3f camray, Vector3f rayOrigin, meshTriangle triangle);

#endif
