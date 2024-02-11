#include "cube.h"

Cube::Cube(const VT* vertices, unsigned int numVertices, const unsigned int* indices, unsigned int numIndices)
    : numIndices(numIndices) {
    createVertexBuffer(vertices, numVertices);
    createIndexBuffer(indices, numIndices);
}

Cube::~Cube() {
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
}

void Cube::createVertexBuffer(const VT* vertices, unsigned int numVertices) {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(VT), vertices, GL_STATIC_DRAW);
}

void Cube::createIndexBuffer(const unsigned int* indices, unsigned int numIndices) {
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void Cube::SetPosition(float x, float y, float z) {
    transform.SetPosition(x, y, z);
}

void Cube::setRotation(float rx, float ry, float rz) {
    transform.SetRotation(rx, ry, rz);
}

void Cube::Draw(const Matrix4f& projection, const Matrix4f& view, GLuint gWVPLocation) {
    Matrix4f world_pose = transform.GetMatrix();
    Matrix4f wvp = projection * view * world_pose;
    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, &wvp.m[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

