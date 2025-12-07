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
    glBindVertexArray(0);
}

void Mesh::LoadData(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &colors, std::vector<glm::vec2> &texCoords)
{
    _mVertices = &vertices;
    _mVerticesColors = &colors;
    _mTexCoords = &texCoords;

    _mVertexCount = vertices.size();

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    size_t verticesSize = vertices.size() * sizeof(glm::vec3);
    size_t colorsSize = colors.size() * sizeof(glm::vec3);
    size_t texCoordsSize = texCoords.size() * sizeof(glm::vec2);

    glBufferData(GL_ARRAY_BUFFER, verticesSize + colorsSize + texCoordsSize, nullptr, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, verticesSize, vertices.data());
    glBufferSubData(GL_ARRAY_BUFFER, verticesSize, colorsSize, colors.data());
    glBufferSubData(GL_ARRAY_BUFFER, verticesSize + colorsSize, texCoordsSize, texCoords.data());

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)verticesSize);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *)(verticesSize + colorsSize));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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
    glBindVertexArray(mVAO);
    if (!_mHasShader)
    {
        glDrawArrays(GL_TRIANGLES, 0, _mVertexCount);
        glBindVertexArray(0);
        return;
    }

    _mShader->Use();
    glDrawArrays(GL_TRIANGLES, 0, _mVertexCount);
    glBindVertexArray(0);
}