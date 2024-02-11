// GameObject.h
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <vector>
#include "world_transform.h" 


//GameOBject constructor needs to have VBO, IBO and gWVPLocation
class GameObject {
public:
    GameObject(GLuint shaderProgramID);
    ~GameObject();

    void Draw(const Matrix4f& Projection, const Matrix4f& View);
    void CreateVertexBuffer();
    void CreateIndexBuffer();

private:
    GLuint VBO, IBO, gWVPLocation;
    GLuint shaderProgramID;
    WorldTrans Transform;
};

class SceneManager {
public:
    std::vector<GameObject> GameObjects;
    Matrix4f Projection, View;

    void AddGameOBject(const GameObject& game_object);

    void SetProjection(const Matrix4f& proj);

    void SetView(const Matrix4f& view);

    void Update();

    void Render();
};


#endif // GAMEOBJECT_H
