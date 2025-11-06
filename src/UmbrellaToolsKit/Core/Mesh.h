#ifndef _MESH_H_
#define _MESH_H_

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Mesh
{
private:
    unsigned int mVBO, mVAO;
    std::vector<glm::vec3> *_mVertices;
    unsigned int _mVertexCount;

public:
    void LoadData(std::vector<glm::vec3> &vertices);
    void Draw();
};

#endif // _MESH_H_