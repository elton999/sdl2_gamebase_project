#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "SquareMesh.h"

class Sprite : public SquareMesh
{
public:
    Sprite() : SquareMesh()
    {
        Shader shader(
            "#version 330 core\n"
            "layout(location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>\n"
            "out vec2 TexCoords;\n"
            "uniform mat4 model;\n"
            "uniform mat4 projection;\n"
            "void main() {\n"
            "    TexCoords = vertex.zw;\n"
            "    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);\n"
            "}\n\0",

            "#version 330 core\n"
            "in vec2 TexCoords;\n"
            "out vec4 color;\n"
            "uniform sampler2D image;\n"
            "uniform vec3 spriteColor;\n"
            "void main()\n"
            "{\n"
            "        color = vec4(spriteColor, 1.0) * texture(image, TexCoords);\n"
            "}\n\0");
        ;
        this->SetShader(shader);
    }
};

#endif // _SPRITE_H_