#ifndef SHADERS_H
#define SHADERS_H


#include "../external/glad/glad.h"
#include "../external/GLFW/glfw3.h"

#include "../external/glm/glm.hpp"
#include "../external/glm/gtc/matrix_transform.hpp"
#include "../external/glm/gtc/type_ptr.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

#include <vector>


class Shader
{
public:
    //id of our shader program
    unsigned int ID;
    
    Shader(const char* vertexPath, const char* fragmentPath);

    void useShader();
    void deleteShader();

    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;
    void setVec3f(const std::string &name, glm::vec3 value) const;
};

#endif