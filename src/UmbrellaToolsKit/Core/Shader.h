#ifndef _SHADER_H_
#define _SHADER_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int ID;

    Shader(const char *vertexCode, const char *fragmentCode);

    void Use();

    void SetBool(const std::string &name, GLboolean value) const;
    void SetInt(const std::string &name, GLint value) const;
    void SetFloat(const std::string &name, GLfloat value) const;
    void SetVec3(const std::string &name, const glm::vec3 &value) const;
    void SetVec2(const std::string &name, const glm::vec2 &value) const;
    void SetMatrix4(const std::string &name, const glm::mat4 value) const;

private:
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif // _SHADER_H_