// GameObject.cpp
#include "game_object.h"


GameObject::GameObject(GLuint shaderProgramID) : shaderProgramID(shaderProgramID) {
    CreateVertexBuffer();
    CreateIndexBuffer();
}

GameObject::~GameObject() {
    // Cleanup VBO, IBO, etc.
    if (VBO) {
        glDeleteBuffers(1, &VBO);
    }
    if (IBO) {
        glDeleteBuffers(1, &IBO);
    }
}

void GameObject::CreateVertexBuffer() {
    VT Vertices[8] = {
    VT(0.1f, 0.1f, 0.1f),
    VT(-0.1f, 0.1f, -0.1f),
    VT(-0.1f, 0.1f, 0.1f),
    VT(0.1f, -0.1f, -0.1f),
    VT(-0.1f, -0.1f, -0.1f),
    VT(0.1f, 0.1f, -0.1f),
    VT(0.1f, -0.1f, 0.1f),
    VT(-0.1f, -0.1f, 0.1f)
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

void GameObject::CreateIndexBuffer() {
    unsigned int Indices[] = {
                              0, 1, 2,
                              1, 3, 4,
                              5, 6, 3,
                              7, 3, 6,
                              2, 4, 7,
                              0, 7, 6,
                              0, 5, 1,
                              1, 5, 3,
                              5, 0, 6,
                              7, 4, 3,
                              2, 1, 4,
                              0, 2, 7
                            };

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

void GameObject::Draw(const Matrix4f& Projection, const Matrix4f& View) {
    glUseProgram(shaderProgramID);
    Matrix4f WVP = Projection * View * Transform.GetMatrix();
    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, &WVP.m[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Enable vertex attribute arrays and set vertex attribute pointers here
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VT), (void*)offsetof(VT, pos));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VT), (void*)offsetof(VT, color));

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}


void SceneManager::AddGameOBject(const GameObject& game_object) {
    GameObjects.push_back(game_object);
}

void SceneManager::SetProjection(const Matrix4f& proj) {
    Projection = proj;
}

void SceneManager::SetView(const Matrix4f& view) {
    View = view;
}

void SceneManager::Update() {
    // Update logic for all cubes if needed
}

void SceneManager::Render() {
    for (auto& game_object : GameObjects) {
        game_object.Draw(Projection, View);
    }
}
