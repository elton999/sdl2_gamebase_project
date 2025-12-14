#include "Sprite.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Sprite::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec4 coords, glm::vec2 scale, float rotate, glm::vec3 color)
{
    this->GetShader()->Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    // 'scale' here is the final desired size in pixels (width, height).
    glm::vec2 baseSize = glm::vec2(coords.z, coords.w);
    glm::vec2 finalSize = baseSize * scale;

    // Center/rotate around the middle of the final size (not the base tex region)
    model = glm::translate(model, glm::vec3(0.5f * finalSize.x, 0.5f * finalSize.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * finalSize.x, -0.5f * finalSize.y, 0.0f));

    model = glm::scale(model, glm::vec3(finalSize, 1.0f));

    this->GetShader()->SetMatrix4("model", model);
    this->GetShader()->SetVec3("spriteColor", color);

    // compute normalized texture region (offset, scale) in [0,1]
    glm::vec2 texOffset = glm::vec2(coords.x / (float)texture.GetWidth(), coords.y / (float)texture.GetHight());
    glm::vec2 texScale = glm::vec2((coords.z - coords.x) / (float)texture.GetWidth(), (coords.w - coords.y) / (float)texture.GetHight());
    this->GetShader()->SetVec2("texOffset", texOffset);
    this->GetShader()->SetVec2("texScale", texScale);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, _mVertexCount);
    glBindVertexArray(0);
}

void Sprite::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec4 coords, float scale, float rotate, glm::vec3 color)
{
    glm::vec2 finalSize = glm::vec2(scale, scale);
    this->DrawSprite(texture, position, coords, finalSize, rotate, color);
}

void Sprite::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
    float scale = 1.0f;
    glm::vec4 coords = glm::vec4(0.0f, 0.0f, size.x, size.y);
    this->DrawSprite(texture, position, coords, scale, rotate, color);
}

void Sprite::DrawSprite(Texture2D &texture, glm::vec2 position, float scale, float rotate, glm::vec3 color)
{
    glm::vec2 size = glm::vec2((float)texture.GetWidth(), (float)texture.GetHight()) * scale;
    this->DrawSprite(texture, position, size, rotate, color);
}

void Sprite::DrawSprite(Texture2D &texture, glm::vec2 position)
{
    glm::vec2 size = glm::vec2((float)texture.GetWidth(), (float)texture.GetHight());
    this->DrawSprite(texture, position, size, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}