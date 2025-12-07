#include "ResourceManager.h"
#include "stb_image.h"
#include "SDL2/SDL_opengl.h"
#include <string>

std::map<std::string, Texture2D *> ResourceManager::_mTextures2D;

Texture2D *ResourceManager::LoadTexture2D(const char *filePath)
{
    std::string key = filePath;

    if (_mTextures2D.find(key) != _mTextures2D.end())
        return _mTextures2D[key];

    Texture2D *texture = new Texture2D();

    texture->Internal_Format = GL_RGBA;
    texture->Image_Format = GL_RGBA;

    int width, height, nrChannels;
    unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);

    if (!data)
    {
        std::cerr << "Failed to load texture: " << filePath << std::endl;
        delete texture;
        return nullptr;
    }

    texture->Generate(width, height, data);
    stbi_image_free(data);

    _mTextures2D[key] = texture;

    return texture;
}