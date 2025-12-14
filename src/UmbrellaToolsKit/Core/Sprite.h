#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Mesh.h"
#include "Texture2D.h"

class Sprite : public Mesh
{
public:
    Sprite()
    {

        std::vector<glm::vec3> square =
            {
                glm::vec3{0.0f, 1.0f, 0.0f},
                glm::vec3{1.0f, 1.0f, 0.0f},
                glm::vec3{0.0f, 0.0f, 0.0f},

                glm::vec3{1.0f, 1.0f, 0.0f},
                glm::vec3{1.0f, 0.0f, 0.0f},
                glm::vec3{0.0f, 0.0f, 0.0f},
            };

        std::vector<glm::vec2> texCoords =
            {
                glm::vec2{0.0f, 1.0f},
                glm::vec2{1.0f, 1.0f},
                glm::vec2{0.0f, 0.0f},

                glm::vec2{1.0f, 1.0f},
                glm::vec2{1.0f, 0.0f},
                glm::vec2{0.0f, 0.0f},
            };

        std::vector<glm::vec3> colors =
            {
                glm::vec3{1.0f, 0.0f, 0.0f},
                glm::vec3{0.0f, 1.0f, 0.0f},
                glm::vec3{0.0f, 0.0f, 1.0f},

                glm::vec3{1.0f, 1.0f, 0.0f},
                glm::vec3{0.0f, 1.0f, 1.0f},
                glm::vec3{1.0f, 0.0f, 1.0f},
            };

        this->LoadData(square, colors, texCoords);

        const char *vertexCode =
            "#version 330 core\n"
            "layout(location = 0) in vec3 position;\n"
            "layout(location = 1) in vec3 vertexColor;\n"
            "layout(location = 2) in vec2 texCoords;\n"
            "out vec2 TexCoords;\n"
            "uniform mat4 model;\n"
            "uniform mat4 projection;\n"
            "void main() {\n"
            "    TexCoords = texCoords;\n"
            "    gl_Position = projection * model * vec4(position, 1.0);\n"
            "}\n";

        const char *fragmentCode =
            "#version 330 core\n"
            "in vec2 TexCoords;\n"
            "out vec4 color;\n"
            "uniform sampler2D image;\n"
            "uniform vec3 spriteColor;\n"
            "// texOffset: (offsetX, offsetY) in normalized coords\n"
            "// texScale:  (scaleX, scaleY) in normalized coords\n"
            "uniform vec2 texOffset;\n"
            "uniform vec2 texScale;\n"
            "void main()\n"
            "{\n"
            "    vec2 uv = texOffset + texScale * TexCoords;\n"
            "    color = vec4(spriteColor, 1.0) * texture(image, uv);\n"
            "}\n";

        Shader *shader = new Shader(vertexCode, fragmentCode);
        // default texture region: full texture
        shader->Use();
        shader->SetVec2("texOffset", glm::vec2(0.0f, 0.0f));
        shader->SetVec2("texScale", glm::vec2(1.0f, 1.0f));
        this->SetShader(*shader);
    }

    void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec4 coords, glm::vec2 scale, float rotate, glm::vec3 color);
    void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec4 coords, float scale, float rotate, glm::vec3 color);
    void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color);
    void DrawSprite(Texture2D &texture, glm::vec2 position, float scale, float rotate, glm::vec3 color);
    void DrawSprite(Texture2D &texture, glm::vec2 position);
};

#endif // _SPRITE_H_