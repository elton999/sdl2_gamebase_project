#ifndef _MESH_H_
#define _MESH_H_

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Shader.h"

class Mesh
{
private:
    unsigned int mVBO, mVAO;
    std::vector<glm::vec3> *_mVertices;
    std::vector<glm::vec3> *_mVerticesColors;
    std::vector<glm::vec2> *_mTexCoords;

    unsigned int _mVertexCount;
    Shader *_mShader;
    bool _mHasShader = false;

public:
    void SetShader(Shader &shader);
    Shader *GetShader();

    void LoadData(std::vector<glm::vec3> &vertices);
    void LoadData(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &colors, std::vector<glm::vec2> &texCoords);
    void Draw();
};

#endif // _MESH_H_