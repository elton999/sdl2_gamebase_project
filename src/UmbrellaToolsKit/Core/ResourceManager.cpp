#include "ResourceManager.h"
#include "stb_image.h"
#include "SDL2/SDL_opengl.h"

Texture2D *ResourceManager::LoadTexture2D(const char filePath)
{
    Texture2D texture2D;

    texture2D.Internal_Format = GL_RGBA;
    texture2D.Image_Format = GL_RGBA;

    int width, height, nrChannels;
    unsigned char *data = stbi_load(&filePath, &width, &height, &nrChannels, 0);

    texture2D.Generate(width, height, data);
    stbi_image_free(data);

    return &texture2D;
}