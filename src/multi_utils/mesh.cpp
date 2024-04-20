#include "mesh.h"
#include <iostream>
#include <limits>

Mesh::Mesh(const VT* vertices, unsigned int numVertices, const unsigned int* indices, unsigned int numIndices)
    : numIndices(numIndices) {

    createVertexBuffer(vertices, numVertices);
    createIndexBuffer(indices, numIndices);
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
}

void Mesh::setID(int id_num){
    obj_id = id_num;
}
void Mesh::createVertexBuffer(const VT* vertices, unsigned int numVertices) {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(VT), vertices, GL_STATIC_DRAW);
}

void Mesh::createIndexBuffer(const unsigned int* indices, unsigned int numIndices) {
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void Mesh::SetPosition(float x, float y, float z) {
    transform.SetPosition(x, y, z);
}

void Mesh::setRotation(float rx, float ry, float rz) {
    transform.SetRotation(rx, ry, rz);
}

void Mesh::translate(float x, float y, float z){
    transform.Translate(x,y,z);
}
void Mesh::rotate(float rx, float ry, float rz){
    transform.Rotate(rx, ry, rz);
}

void Mesh::Draw(const Matrix4f& projection, const Matrix4f& view, GLuint gWVPLocation) {
    glUseProgram(shaderProgramID);
    Matrix4f world_pose = transform.GetMatrix();
    Matrix4f wvp = projection * view * world_pose;
    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, &wvp.m[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));

    glDrawElements(GL_TRIANGLES,numIndices, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void Mesh::DrawLine(const Matrix4f& projection, const Matrix4f& view, GLuint gWVPLocation) {
    glUseProgram(shaderProgramID);
    Matrix4f world_pose = transform.GetMatrix();
    Matrix4f wvp = projection * view * world_pose;
    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, &wvp.m[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));

    glDrawElements(GL_LINES, numIndices, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}


void Mesh::SetShaderProgram(GLuint programID) {
    shaderProgramID = programID;
}



void draw_triangles(const std::vector<std::shared_ptr<Mesh>>& game_objects, Matrix4f Projection, Matrix4f View, GLuint gWVPLocation) {
    for (const auto& meshPtr : game_objects) {
        if (meshPtr) { // Check if the shared_ptr is not null
            meshPtr->Draw(Projection, View, gWVPLocation);
        }
    }
}

void draw_lines(const std::vector<std::shared_ptr<Mesh>>& game_objects, Matrix4f Projection, Matrix4f View, GLuint gWVPLocation) {
    for (const auto& meshPtr : game_objects) {
        if (meshPtr) { // Check if the shared_ptr is not null
            meshPtr->DrawLine(Projection, View, gWVPLocation);
        }
    }
}

VT* generateSquareVertices(float sideLength) {

    int numVertices = 4; // A square has four vertices
    VT* vertices = new VT[numVertices];

    vertices[0] = VT(0.0f, 0.0f, 0.0f, 0.95, 0.95, 0.95);            // Bottom Left
    vertices[1] = VT(0.0f, 0.0f, sideLength, 0.95, 0.95, 0.95);      // Bottom Right
    vertices[2] = VT(sideLength, 0.0f, sideLength, 0.95, 0.95, 0.95); // Top Right
    vertices[3] = VT(sideLength, 0.0f, 0.0f, 0.95, 0.95, 0.95);      // Top Left

    return vertices;
}

unsigned int* generateSquareIndices() {
    // For a square outline, we need 8 indices (2 per edge)
    int numIndices = 8;
    unsigned int* indices = new unsigned int[numIndices];

    indices[0] = 0; indices[1] = 1; // Bottom edge
    indices[2] = 1; indices[3] = 2; // Right edge
    indices[4] = 2; indices[5] = 3; // Top edge
    indices[6] = 3; indices[7] = 0; // Left edge

    return indices;
}

void move_mesh(std::shared_ptr<Mesh> mesh_ptr, unsigned char key){
    
    switch (key){
        case 'i':
        case 'I':
        {
            std::cout<<"z +0.25"<<std::endl;
            mesh_ptr->translate(0,0,0.25);
            break;
        }

        case 'k':
        case 'K':
        {
            std::cout<<"z -0.25"<<std::endl;
            mesh_ptr->translate(0,0,-0.25);
            break;
        }

        case 'j':
        case 'J':
        {
            std::cout<<"x -0.25"<<std::endl;
            mesh_ptr->translate(-0.25,0,0);
            break;
        }

        case 'l':
        case 'L':
        {
            std::cout<<"x +0.25"<<std::endl;
            mesh_ptr->translate(0.25,0,0);
            break;
        }
    }
}



meshTriangle::meshTriangle(Vector3f p1, Vector3f p2, Vector3f p3) {
    a = p1;
    b = p2;
    c = p3;
}

//gets all triangles in mesh
//size is numbr of triangles in mesh
std::vector<meshTriangle> get3DTriangle(VT* verticies, WorldTrans transform, int size){
    std::vector<meshTriangle> result;
    Matrix4f world_pose = transform.GetMatrix();

    float dx = transform.GetMatrix().m[0][3];
    float dy = transform.GetMatrix().m[1][3];
    float dz = transform.GetMatrix().m[2][3];
    Vector3f ds(dx,dy,dz);
    for (int i =0; i < size-2; i++){
        int k1 = i;
        int k2 = i+1;
        int k3 = i+2;
        Vector3f p1 = verticies[k1].pos + ds;
        Vector3f p2 = verticies[k2].pos + ds;
        Vector3f p3 = verticies[k3].pos + ds;
        result.push_back(meshTriangle(p1, p2, p3));
        
    }
    //2nd last

    Vector3f p2f1 = verticies[size-1].pos + ds;
    Vector3f p2f2 = verticies[size].pos + ds;
    Vector3f p2f3 = verticies[0].pos + ds;
    result.push_back(meshTriangle(p2f1, p2f2, p2f3));
    
    //last
    Vector3f pf1 = verticies[size].pos + ds;
    Vector3f pf2 = verticies[0].pos + ds;
    Vector3f pf3 = verticies[1].pos +ds;
    result.push_back(meshTriangle(pf1, pf2, pf3));
    int triangle_count = 1;
    for (auto triangle : result){
        Vector3f p1 = triangle.a;
        Vector3f p2 = triangle.b;
        Vector3f p3 = triangle.c;
        std::cout<<"triangle "<<triangle_count<<std::endl;
        printTrianglePoint(p1);
        printTrianglePoint(p2);
        printTrianglePoint(p3);
        triangle_count +=1;
        std::cout<<" "<<std::endl;

    }

    return result;
    
}
void printTrianglePoint(Vector3f p){
    std::cout<<p.x;
    std::cout<<" ,";
    std::cout<<p.y;
    std::cout<<" ,";
    std::cout<<p.z<<std::endl;
   
}

bool intersectTest(Vector3f camray, Vector3f rayOrigin, meshTriangle triangle) {
    constexpr float epsilon = std::numeric_limits<float>::epsilon();

    Vector3f edge1 = triangle.b - triangle.a;
    Vector3f edge2 = triangle.c - triangle.a;
    Vector3f ray_cross_e2 = camray.Cross(edge2);
    float det = edge1.Dot(ray_cross_e2);

    // Parallel check
    if (det > -epsilon && det < epsilon) {
        return false;    
    }

    float inv_det = 1.0f / det;
    Vector3f s = rayOrigin - triangle.a; 
    float u = inv_det * s.Dot(ray_cross_e2);

    // Bounds check for U parameter
    if (u < 0.0f || u > 1.0f) {
        return false;
    }

    Vector3f s_cross_e1 = s.Cross(edge1);
    float v = inv_det * camray.Dot(s_cross_e1);

    // Bounds check for V parameter, and combined U+V <= 1 for inside triangle
    if (v < 0.0f || u + v > 1.0f) {
        return false;
    }

    // Calculate t to find the intersection point
    float t = inv_det * edge2.Dot(s_cross_e1);

    // Check if t is within the acceptable range (> epsilon)
    if (t > epsilon) {
        // Calculate the exact intersection point
        Vector3f out_intersection_point = rayOrigin + camray * t;
        
        return true;
    } else {
        // Line intersects, but not in the ray's direction
        return false;
    }
}
