#include "mesh.h"
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

    vertices[0] = VT(0.0f, 0.0f, 0.0f);            // Bottom Left
    vertices[1] = VT(0.0f, 0.0f, sideLength);      // Bottom Right
    vertices[2] = VT(sideLength, 0.0f, sideLength); // Top Right
    vertices[3] = VT(sideLength, 0.0f, 0.0f);      // Top Left

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