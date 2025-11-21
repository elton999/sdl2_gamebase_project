#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANGER_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <string>

#include "UmbrellaToolsKit/Core/Texture2D.h"

class ResourceManager
{
private:
    static std::map<std::string, Texture2D *> _mTextures2D;

public:
    static Texture2D *LoadTexture2D(const char filePath);
};

#endif //_RESOURCE_MANGER_H_