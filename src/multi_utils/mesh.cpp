#include "mesh.h"
#include <iostream>
//    unsigned int n_v = numVertices;
//     unsigned int n_i = numIndices;

Mesh::Mesh(const VT* vertices, unsigned int numVertices, const unsigned int* indices, unsigned int numIndices)
    : numIndices(numIndices) {

    createVertexBuffer(vertices, numVertices);
    createIndexBuffer(indices, numIndices);
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
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

    // Assuming vertices are ordered as follows:
    // 0: bottom left, 1: bottom right, 2: top right, 3: top left
    // Outline of the square
    indices[0] = 0; indices[1] = 1; // Bottom edge
    indices[2] = 1; indices[3] = 2; // Right edge
    indices[4] = 2; indices[5] = 3; // Top edge
    indices[6] = 3; indices[7] = 0; // Left edge

    return indices;
}

VT* generateGridVertices(int sideLength) {
   
    if (sideLength < 2) {
        //sideLength must be atleast 3
        std::cout<<"side length must be atleast 3, rendering 3"<<std::endl;
        sideLength = 2;
        
    }

    int numVertices = (sideLength - 1) * 4; // Number of vertices for the grid perimeter
    VT* vertices = new VT[numVertices];

    int index = 0;

    // Bottom side
    for (int x = 0; x < sideLength - 1; x++) {
        vertices[index++] = VT(x, 0, 0, 0.95, 0.95, 0.95);
    }

    // Right side
    for (int z = 0; z < sideLength - 1; ++z) {
        vertices[index++] = VT(sideLength - 1, 0, z, 0.95, 0.95, 0.95);
    }

    // Top side (going backwards on x)
    for (int x = sideLength - 1; x > 0; --x) {
        vertices[index++] = VT(x, 0, sideLength - 1, 0.95, 0.95, 0.95);
    }

    // Left side (going backwards on z)
    for (int z = sideLength - 1; z > 0; --z) {
        vertices[index++] = VT(0, 0, z, 0.95, 0.95, 0.95);
    }

    return vertices;
}

unsigned int* generateGridIndices(int sideLength) {
    // Each cell of the grid will have 2 lines (horizontal and vertical),
    // and there are (sideLength - 1) squares along each side of the grid.
    int numLines = 2 * (sideLength - 1);
    // Each line is defined by 2 indices (start and end), hence * 2.
    int numIndices = numLines * 2;
    unsigned int* indices = new unsigned int[numIndices];

    // Calculate horizontal lines' indices
    for (int i = 0; i < sideLength - 1; ++i) {
        indices[i * 2] = i;
        indices[i * 2 + 1] = i + (sideLength - 1) * 3;
    }

    // Calculate vertical lines' indices
    int offset = (sideLength - 1) * 2; // Offset to start of vertical lines in indices array
    for (int i = 0; i < sideLength - 1; ++i) {
        indices[offset + i * 2] = (sideLength - 1) * 2 - i;
        indices[offset + i * 2 + 1] = (sideLength - 1) * 4 - i - 1;
    }

    return indices;
}