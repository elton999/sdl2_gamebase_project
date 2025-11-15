#ifndef _SHADER_H_
#define _SHADER_H_

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
    std::string *_vertexCode;
    std::string *_fragmentCode;

    void checkCompileErrors(unsigned int shader, std::string type);

public:
    unsigned int ID;

    Shader(const char *vertexCode, const char *fragmentCode);

    void Use();

    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
};

#endif // _SHADER_H_