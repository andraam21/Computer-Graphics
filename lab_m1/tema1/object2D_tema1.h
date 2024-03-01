#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D_tema1
{
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color, bool fill);
    Mesh* CreateStar(const std::string& name, float ind, float radius, glm::vec3 color, bool fill);
    Mesh* CreateGun(const std::string& name, glm::vec3 color, bool fill);
    Mesh* CreateHexagon(const std::string& name,float ind, float radius, glm::vec3 color, glm::vec3 color1, bool fill);
    Mesh* CreateHeart(const std::string& name, glm::vec3 color, bool fill);
}
