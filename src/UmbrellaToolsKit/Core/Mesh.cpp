#include "Mesh.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

void Mesh::LoadData(std::vector<glm::vec3> &vertices)
{
    _mVertices = &vertices;
    _mVertexCount = vertices.size();
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::SetShader(Shader &shader)
{
    _mShader = &shader;
    _mHasShader = true;
}

Shader *Mesh::GetShader()
{
    return _mShader;
}

void Mesh::Draw()
{
    if (!_mHasShader)
    {
        glDrawArrays(GL_TRIANGLES, 0, _mVertexCount);
        return;
    }

    _mShader->Use();
    glDrawArrays(GL_TRIANGLES, 0, _mVertexCount);
}