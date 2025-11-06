#ifndef _SQUARE_MESH_H_
#define _SQUARE_MESH_H_

#include "Mesh.h"

class SquareMesh : public Mesh
{
public:
    SquareMesh()
    {
        std::vector<glm::vec3> Square =
            {
                glm::vec3{0.0f, 1.0f, 0.0f},
                glm::vec3{1.0f, 1.0f, 0.0f},
                glm::vec3{0.0f, 0.0f, 0.0f},

                glm::vec3{1.0f, 1.0f, 0.0f},
                glm::vec3{1.0f, 0.0f, 0.0f},
                glm::vec3{0.0f, 0.0f, 0.0f},
            };
        LoadData(Square);
    }
};

#endif // _SQUARE_MESH_H_