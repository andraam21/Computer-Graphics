#include "object2D_tema1.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D_tema1::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D_tema1::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D_tema1::CreateStar(
    const std::string& name,
    float ind,
    float radius,
    glm::vec3 color,
    bool fill)

{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(3 * ind * cos(radius), 3 * ind * sin(radius), 2), color),
        VertexFormat(glm::vec3(ind * cos(3 * radius), ind * sin(3 * radius), 2), color),
        VertexFormat(glm::vec3(3 * ind * cos(5 * radius), 3 * ind * sin(5 * radius), 2), color),
        VertexFormat(glm::vec3(ind * cos(7 * radius), ind * sin(7 * radius), 2), color),
        VertexFormat(glm::vec3(3 * ind * cos(9 * radius), 3 * ind * sin(9 * radius), 2), color),
        VertexFormat(glm::vec3(ind * cos(11 * radius), ind * sin(11 * radius), 2), color),
        VertexFormat(glm::vec3(3 * ind * cos(13 * radius), 3 * ind * sin(13 * radius), 2), color),
        VertexFormat(glm::vec3(ind * cos(15 * radius), ind * sin(15 * radius), 2), color),
        VertexFormat(glm::vec3(3 * ind * cos(17 * radius), 3 * ind * sin(17 * radius), 2), color),
        VertexFormat(glm::vec3(ind * cos(19 * radius), ind * sin(19 * radius), 2), color),
 
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = { 
        3, 1, 2,
        1, 9, 0,
        9, 7, 8,
        7, 5, 6,
        5, 3, 4,
        5, 1, 3,
        5, 7, 9,
        5, 9, 1,
     };

  
    star->InitFromData(vertices, indices);
    return star;
}

Mesh* object2D_tema1::CreateGun(
    const std::string& name,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0, 2, 1), color),
        VertexFormat(glm::vec3(-1, 0, 1), color),
        VertexFormat(glm::vec3(0, -2, 1), color),
        VertexFormat(glm::vec3(1, 0, 1), color),
        VertexFormat(glm::vec3(0, 0.5f, 1), color),
        VertexFormat(glm::vec3(2, 0.5f, 1), color),
        VertexFormat(glm::vec3(2, -0.5f, 1), color),
        VertexFormat(glm::vec3(0, -0.5f, 1), color),
    };

    Mesh* gun = new Mesh(name);
    std::vector<unsigned int> indices = { 
        1, 0, 3,
        2, 1, 3,
        7, 4, 5,
        6, 7, 5,
    };

 
    gun->InitFromData(vertices, indices);
    return gun;
}

Mesh* object2D_tema1::CreateHexagon(
    const std::string& name,
    float ind,
    float radius,
    glm::vec3 color,
    glm::vec3 color1,
    bool fill)

{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(1.5f * ind * cos(radius), 1.5f * ind * sin(radius), 1), color1),
        VertexFormat(glm::vec3(ind * cos(radius), ind * sin(radius), 1), color1),
        VertexFormat(glm::vec3(1.5f * ind * cos(5 * radius), 1.5f * ind * sin(5 * radius), 1), color1),
        VertexFormat(glm::vec3(ind * cos(5 * radius), ind * sin(5 * radius), 1), color1),
        VertexFormat(glm::vec3(1.5f * ind * cos(9 * radius), 1.5f * ind * sin(9 * radius), 1), color1),
        VertexFormat(glm::vec3(ind * cos(9 * radius), ind * sin(9 * radius), 1), color1),
        VertexFormat(glm::vec3(1.5f * ind * cos(13 * radius), 1.5f * ind * sin(13 * radius), 1), color1),
        VertexFormat(glm::vec3(ind * cos(13 * radius), ind * sin(13 * radius), 1), color1),
        VertexFormat(glm::vec3(1.5f * ind * cos(17 * radius), 1.5f * ind * sin(17 * radius), 1), color1),
        VertexFormat(glm::vec3(ind * cos(17 * radius), ind * sin(17 * radius), 1), color1),
        VertexFormat(glm::vec3(ind * cos(radius), ind * sin(radius), 1), color),
        VertexFormat(glm::vec3(ind * cos(5 * radius), ind * sin(5 * radius), 1), color),
        VertexFormat(glm::vec3(ind * cos(9 * radius), ind * sin(9 * radius), 1), color),
        VertexFormat(glm::vec3(ind * cos(13 * radius), ind * sin(13 * radius), 1), color),
        VertexFormat(glm::vec3(ind * cos(17 * radius), ind * sin(17 * radius), 1), color),
    };

    Mesh* hexagon = new Mesh(name);
    std::vector<unsigned int> indices = {
        4, 3, 2,
        3, 1, 2,
        2, 1, 0,
        1, 9, 0,
        0, 9, 8,
        8, 7, 6,
        6, 5, 4,
        9, 7, 8,
        7, 5, 6,
        5, 3, 4,
        12, 10, 11,
        12, 13, 14,
        12, 14, 10,
    };


    hexagon->InitFromData(vertices, indices);
    return hexagon;
}

Mesh* object2D_tema1::CreateHeart(
    const std::string& name,
    glm::vec3 color,
    bool fill)

{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(1.5f, 2.5f, 2), color),
        VertexFormat(glm::vec3(2, 3, 2), color),
        VertexFormat(glm::vec3(3, 3, 2), color),
        VertexFormat(glm::vec3(3, 2, 2), color),
        VertexFormat(glm::vec3(1.5f, 0.5f, 2), color),
        VertexFormat(glm::vec3(0, 2, 2), color),
        VertexFormat(glm::vec3(0, 3, 2), color),
        VertexFormat(glm::vec3(1, 3, 2), color),
        VertexFormat(glm::vec3(2, 2, 3), glm::vec3(1, 1, 1)),
        VertexFormat(glm::vec3(2.25f, 2.35f, 3), glm::vec3(1, 1, 1)),
        VertexFormat(glm::vec3(2.6f, 2, 3), glm::vec3(1, 1, 1)),

 
    };

    Mesh* heart = new Mesh(name);
    std::vector<unsigned int> indices = {
        5, 3, 4,
        5, 0, 3,
        1, 2, 3,
        0, 1, 3,
        7, 0, 5,
        6, 7, 5,
        8, 9, 10,
    };


    heart->InitFromData(vertices, indices);
    return heart;
}



