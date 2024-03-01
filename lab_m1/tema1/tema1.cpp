
#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <random>

#include "lab_m1/tema1/transform2D_tema1.h"
#include "lab_m1/tema1/object2D_tema1.h"

using namespace std;
using namespace m1;


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // Logic space
    logicSpace.x = 0;       
    logicSpace.y = 0;       
    logicSpace.width = 12;  
    logicSpace.height = 6;       


    // Table initialisation
    int k = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 1; j <= 3; j++) {
            for (int m = 0; m < 5; m++) {
                table[k].bullets[m].rot = 0;
                table[k].bullets[m].x = j * 1.3f + square_length / 2;
                table[k].bullets[m].y = 0.5f + i * 1.3f + square_length / 2;
                table[k].bullets[m].yes = false;
                table[k].bullets[m].color = "";
            }
            table[k].shoot_time = 0;
            table[k].life = 1;
            table[k].scale = 1;
            table[k].star_count = 0;
            table[k].occupated = false;
            table[k].erase = false;
            table[k].color = "";
            table[k].radius = 0;
            table[k].x = j * 1.3f + square_length / 2;
            table[k].y = 0.5f + i * 1.3f + square_length / 2;
            k++;
        }
    }

    // Enemies
    for (int i = 0; i < 3; i++) {
        enemies[i].x = logicSpace.width;
        enemies[i].y = square_length + i * 1.3f;
        enemies[i].move = false;
        enemies[i].color = ""; 
        enemies[i].life = 3;
        enemies[i].scale = 0.5f;
    }

    // Money 
    for (int i = 0; i < 3; i++) {
        money[i].x = -1;
        money[i].y = -1;
        money[i].yes = false;

    }

    // Meshes
 
    Mesh* square_full = object2D_tema1::CreateSquare("square_full", corner, square_length, glm::vec3(0.2f, 0, 0.5f), true);
    AddMeshToList(square_full);

    Mesh* square_empty = object2D_tema1::CreateSquare("square_empty", corner, square_length, glm::vec3(0, 0, 0), false);
    AddMeshToList(square_empty);

    Mesh* square_life = object2D_tema1::CreateHeart("square_life", glm::vec3(0.8f, 0, 0), true);
    AddMeshToList(square_life);

    Mesh* rectangle = object2D_tema1::CreateRectangle("rectangle", corner, rect_len, rect_hei, glm::vec3(0, 0.5f, 1), true);
    AddMeshToList(rectangle);

    Mesh* star_gray = object2D_tema1::CreateStar("star_gray", 0.05f, rad, glm::vec3(0.5f, 0.5f, 0.5f), true);
    AddMeshToList(star_gray);

    Mesh* star_money = object2D_tema1::CreateStar("star_money", 0.05f, rad, glm::vec3(1, 0.5f, 0.7f), true);
    AddMeshToList(star_money);

    Mesh* star_orange = object2D_tema1::CreateStar("star_orange", 0.05f, rad, glm::vec3(1, 0.5f, 0.3f), true);
    AddMeshToList(star_orange);

    Mesh* star_blue = object2D_tema1::CreateStar("star_blue", 0.05f, rad, glm::vec3(0.5f, 1, 1), true);
    AddMeshToList(star_blue);

    Mesh* star_yellow = object2D_tema1::CreateStar("star_yellow", 0.05f, rad, glm::vec3(1, 1, 0.5f), true);
    AddMeshToList(star_yellow);

    Mesh* star_purple = object2D_tema1::CreateStar("star_purple", 0.05f, rad, glm::vec3(0.7f, 0.6f, 1), true);
    AddMeshToList(star_purple);

    Mesh* orange_gun = object2D_tema1::CreateGun("orange_gun", glm::vec3(1, 0.5f, 0.3f), true);
    AddMeshToList(orange_gun);

    Mesh* blue_gun = object2D_tema1::CreateGun("blue_gun", glm::vec3(0.5f, 1, 1), true);
    AddMeshToList(blue_gun);

    Mesh* yellow_gun = object2D_tema1::CreateGun("yellow_gun", glm::vec3(1, 1, 0.5f), true);
    AddMeshToList(yellow_gun);

    Mesh* purple_gun = object2D_tema1::CreateGun("purple_gun", glm::vec3(0.7f, 0.6f, 1), true);
    AddMeshToList(purple_gun);

    Mesh* hexagon_blue = object2D_tema1::CreateHexagon("hexagon_blue", 0.5f, rad, glm::vec3(0.5f, 0.7f, 0.9f), glm::vec3(0.5f, 1, 1), true);
    AddMeshToList(hexagon_blue);

    Mesh* hexagon_orange = object2D_tema1::CreateHexagon("hexagon_orange", 0.5f, rad, glm::vec3(0.5f, 0.3f, 0), glm::vec3(1, 0.5f, 0.3f), true);
    AddMeshToList(hexagon_orange);

    Mesh* hexagon_purple = object2D_tema1::CreateHexagon("hexagon_purple", 0.5f, rad, glm::vec3(0.3f, 0, 0.5f), glm::vec3(0.7f, 0.6f, 1), true);
    AddMeshToList(hexagon_purple);

    Mesh* hexagon_yellow = object2D_tema1::CreateHexagon("hexagon_yellow", 0.5f, rad, glm::vec3(0.5f, 0.5f, 0), glm::vec3(1, 1, 0.5f), true);
    AddMeshToList(hexagon_yellow);
}


glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}


glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void Tema1::SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0.1f, 0.1f, 0.1f), true);

    // Compute the 2D visualization matrix
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
  
    DrawScene(visMatrix);  

    // Update timer
    frame += deltaTimeSeconds;
    for(int i = 0; i < 9; i++) {
        table[i].shoot_time += deltaTimeSeconds;
        if (table[i].shoot_time > 2) {
            table[i].shoot_time = 0;
        }
    }

    // Random enemies
    random = rand() % 5 + 1;
    if ((int)frame % (int)random == 2) {
        int pos = rand() % 3;
        if (!enemies[pos].move) {
            enemies[pos].move = true;
            enemies[pos].life = 3;
            enemies[pos].x = 12;
            enemies[pos].scale = 0.5f;
            enemies[pos].color = random_colors[rand() % 4];
        }
    }

    // Random money
    random = rand() % 5 + 1;
    if ((int)frame % (int)random == 2) {
        int pos = rand() % 3;
        if (!money[pos].yes) {
            money[pos].rot = rand() % 360;
            money[pos].x = rand() % 12;
            money[pos].y = rand() % 5;
            money[pos].yes = true;
        }
    }


    // Shoot
    for (int i = 0; i < 9; i++) {
        if (enemies[i / 3].color == table[i].color && table[i].occupated && table[i].shoot_time >= 0.5f) {
            table[i].bullets[table[i].star_count].yes = true;
            table[i].bullets[table[i].star_count].color = table[i].color;
            table[i].star_count += 1;
            table[i].shoot_time = 0;
            if (table[i].star_count == 5) {
                table[i].star_count = 0;
            }
            
        }
    }

    // Update star coordinates and disappearance of the gun
    for (int i = 0; i < 9; i++) {
        // Kill the gun
        if (table[i].occupated) {
            if (table[i].life <= 0) {                
                if (table[i].erase) {
                    table[i].y -= 3.0f * deltaTimeSeconds;
                }
                else {
                    table[i].scale -= 1.1f * deltaTimeSeconds;
                }
            }               
        }
       
        // Send the bullets
        for (int j = 0; j < 5; j++) {
            if (table[i].bullets[j].yes) {
                table[i].bullets[j].x += 3.5 * deltaTimeSeconds;
                table[i].bullets[j].rot -= 3 * deltaTimeSeconds;
            }
            if (table[i].bullets[j].x >= 12) {
                table[i].bullets[j].yes = false;
                table[i].bullets[j].x = table[i].x;
            }
        }
    }

    // Update enemy coordinates
    for (int i = 0; i < 3; i++) {
        if (enemies[i].move && enemies[i].life > 0) {
            enemies[i].x -= (0.01f * deltaTimeSeconds + frame * 0.0005f);
        }
        else if (enemies[i].move && enemies[i].life <= 0) {
            enemies[i].scale -= 1.5f * deltaTimeSeconds;
        }
    }


}


void Tema1::FrameEnd()
{
}


void Tema1::DrawScene(glm::mat3 visMatrix)
{
    // The green table matrix

    float beg_matrix_col = square_length + 0.3f;
    float beg_matrix_row = 0.5f;
    float matrix_step = square_length + 0.3f;

    for (int i = 0; i < 3; i++) {
        for (int j = 1; j <= 3; j++) {
            modelMatrix = visMatrix * transform2D::Translate(j * beg_matrix_col, beg_matrix_row + i * matrix_step);
            RenderMesh2D(meshes["square_full"], shaders["VertexColor"], modelMatrix);
        }
    }

    // Red rectangle

    float beg_scene = 0.4f;

    if (number_of_life > 0) {
        modelMatrix = visMatrix * transform2D::Translate(beg_scene, beg_matrix_row) * transform2D::Scale(((float)number_of_life / 3), 1);
        RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);
    }
   
    // Big empty squares & Star gray meshes

    float up = 5;
    float empty_sq_step = square_length + 0.5f;

    // Orange

    modelMatrix = visMatrix * transform2D::Translate(beg_scene + 0.4f, up + 0.5f) * transform2D::Scale(0.2f, 0.2f);
    RenderMesh2D(meshes["orange_gun"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(beg_scene, up);
    RenderMesh2D(meshes["square_empty"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(beg_scene + 0.1f , up - 0.2f);
    RenderMesh2D(meshes["star_gray"], shaders["VertexColor"], modelMatrix);

    // Blue

    modelMatrix = visMatrix * transform2D::Translate(beg_scene + empty_sq_step + 0.4f, up + 0.5f) * transform2D::Scale(0.2f, 0.2f);
    RenderMesh2D(meshes["blue_gun"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(beg_scene + empty_sq_step, up);
    RenderMesh2D(meshes["square_empty"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(beg_scene + empty_sq_step + 0.1f, up - 0.2f);
    RenderMesh2D(meshes["star_gray"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(beg_scene + empty_sq_step + 0.4f, up - 0.2f);
    RenderMesh2D(meshes["star_gray"], shaders["VertexColor"], modelMatrix);

    // Yellow

    modelMatrix = visMatrix * transform2D::Translate(beg_scene + 2 * empty_sq_step + 0.4f, up + 0.5f) * transform2D::Scale(0.2f, 0.2f);
    RenderMesh2D(meshes["yellow_gun"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(beg_scene + 2 * empty_sq_step, up);
    RenderMesh2D(meshes["square_empty"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(beg_scene + 2 * empty_sq_step + 0.1f, up - 0.2f);
    RenderMesh2D(meshes["star_gray"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(beg_scene + 2 * empty_sq_step + 0.4f, up - 0.2f);
    RenderMesh2D(meshes["star_gray"], shaders["VertexColor"], modelMatrix);

    // Purple

    modelMatrix = visMatrix * transform2D::Translate(beg_scene + 3 * empty_sq_step + 0.4f, up + 0.5f) * transform2D::Scale(0.2f, 0.2f);
    RenderMesh2D(meshes["purple_gun"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(beg_scene + 3 * empty_sq_step, up);
    RenderMesh2D(meshes["square_empty"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(beg_scene + 3 * empty_sq_step + 0.1f, up - 0.2f);
    RenderMesh2D(meshes["star_gray"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(beg_scene + 3 * empty_sq_step + 0.4f, up - 0.2f);
    RenderMesh2D(meshes["star_gray"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(beg_scene + 3 * empty_sq_step + 0.7f, up - 0.2f);
    RenderMesh2D(meshes["star_gray"], shaders["VertexColor"], modelMatrix);

    

    // Red square life
    float beg_life = 7.3f;
    float row_life = 5.1f;
    float step_life = square_length + 0.1f;    

    for (int i = 0; i < number_of_life; i++) {
        modelMatrix = visMatrix * transform2D::Translate(beg_life + i * step_life, row_life);
        modelMatrix *= transform2D::Scale(0.3f, 0.3f);
        RenderMesh2D(meshes["square_life"], shaders["VertexColor"], modelMatrix);
    }

    // Money
    for (int i = 0; i < star_money; i++) {
        modelMatrix = visMatrix * transform2D::Translate(beg_life + 0.1f + i * 0.3f, row_life - 0.3f);
        RenderMesh2D(meshes["star_gray"], shaders["VertexColor"], modelMatrix);
    }

    // Star money
    for (int i = 0; i < 3; i++) {
        if (money[i].yes) {
            modelMatrix = visMatrix * transform2D::Translate(money[i].x, money[i].y) * transform2D::Scale(3, 3) * transform2D::Rotate(money[i].rot);
            RenderMesh2D(meshes["star_money"], shaders["VertexColor"], modelMatrix);
        }
    }
  
    // Dragging 
    if (dragging.drag) {      
        modelMatrix = visMatrix * transform2D::Translate(window->GetCursorPosition().x / sx, (window->GetResolution().y - window->GetCursorPosition().y) / sy) * transform2D::Scale(0.2f, 0.2f);
        RenderMesh2D(meshes[dragging.color + "_gun"], shaders["VertexColor"], modelMatrix);
    }

   
    // Dropping
    for (int i = 0; i < 9; i++) {
        // Send every star
        for (int j = 0; j < 5; j++) {
            if (table[i].bullets[j].yes) {
                modelMatrix = visMatrix * transform2D::Translate(table[i].bullets[j].x, table[i].bullets[j].y) * transform2D::Rotate(table[i].bullets[j].rot);
                modelMatrix *= transform2D::Scale(2.5f, 2.5f);
                RenderMesh2D(meshes["star_" + table[i].bullets[j].color], shaders["VertexColor"], modelMatrix);                             

                // Collision star - enemy
                if (enemies[i / 3].x - table[i].bullets[j].x <= 0.5f && table[i].bullets[j].yes && enemies[i / 3].move
                    && enemies[i / 3].color == table[i].bullets[j].color) {
                    enemies[i / 3].life -= 1;
                    table[i].bullets[j].yes = false;
                    table[i].bullets[j].x = table[i].x;
                }
            }
        }
        // Gun position
        if (table[i].occupated) {
            if (table[i].life == 1) {
                modelMatrix = visMatrix * transform2D::Translate(table[i].x, table[i].y) * transform2D::Scale(0.2f, 0.2f);
                RenderMesh2D(meshes[table[i].color + "_gun"], shaders["VertexColor"], modelMatrix);
                
                // Collision enemy - gun
                if (enemies[i / 3].x - table[i].x <= 0.4f && table[i].occupated && enemies[i / 3].move) {                    
                    table[i].life -= 1;
                }
            }
            else {
                // Dissapearance of the gun
                modelMatrix = visMatrix * transform2D::Translate(table[i].x, table[i].y) * transform2D::Scale(0.2f, 0.2f);
                modelMatrix *= transform2D::Scale(table[i].scale, table[i].scale);
                RenderMesh2D(meshes[table[i].color + "_gun"], shaders["VertexColor"], modelMatrix);

                if (table[i].scale <= 0.1f || table[i].y < 0.3f) {                   
                    table[i].erase = false;
                    table[i].occupated = false;
                    table[i].life = 1;
                    table[i].scale = 1;
                    table[i].y = (i / 3) * 1.3f + 1.0f;
                }
               
            }
            
        }
    }

    // Enemies    
    for (int i = 0; i < 3; i++) {
        if (enemies[i].scale <= 0.1f) {
            enemies[i].move = false;
        }
        if (enemies[i].move && enemies[i].life > 0) {
            modelMatrix = visMatrix * transform2D::Translate(enemies[i].x, enemies[i].y) * transform2D::Scale(0.5f, 0.5f) * transform2D::Rotate(70);
            RenderMesh2D(meshes["hexagon_" + enemies[i].color], shaders["VertexColor"], modelMatrix);
            
            // Lost a life, enemy arrives at the finish line
            if (enemies[i].x <= 0.5f) {                
                enemies[i].move = false;
                number_of_life -= 1;
            }
        }
        else if (enemies[i].move && enemies[i].life <= 0) {
            // Enemy dissapearance using scale
            modelMatrix = visMatrix * transform2D::Translate(enemies[i].x, enemies[i].y) * transform2D::Scale(enemies[i].scale, enemies[i].scale) * transform2D::Rotate(70);
            RenderMesh2D(meshes["hexagon_" + enemies[i].color], shaders["VertexColor"], modelMatrix);
        }
    }

           
}



void Tema1::OnInputUpdate(float deltaTime, int mods)
{   

}


void Tema1::OnKeyPress(int key, int mods)
{
   
}


void Tema1::OnKeyRelease(int key, int mods)
{
   
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
   
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    sx = window->GetResolution().x / logicSpace.width;
    sy = window->GetResolution().y / logicSpace.height;

    logic_mouse_x = mouseX / sx;
    logic_mouse_y = (window->GetResolution().y - mouseY) / sy;


    // Move the gun
    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        
       if (logic_mouse_x > 0.4f && logic_mouse_x < 1.4f && logic_mouse_y < 5.75f && logic_mouse_y > 4.75f) {
           dragging.color = "orange";
           dragging.price = 1;
           dragging.drag = true;
       }
       if (logic_mouse_x > 1.9f && logic_mouse_x < 2.9f && logic_mouse_y < 5.75f && logic_mouse_y > 4.75f) {
           dragging.color = "blue";
           dragging.price = 2;
           dragging.drag = true;
       }
       if (logic_mouse_x > 3.4f && logic_mouse_x < 4.4f && logic_mouse_y < 5.75f && logic_mouse_y  > 4.75f) {
           dragging.color = "yellow";
           dragging.price = 2;
           dragging.drag = true;
       }
       if (logic_mouse_x > 4.9f && logic_mouse_x < 5.9f && logic_mouse_y < 5.75f && logic_mouse_y  > 4.75f) {
           dragging.color = "purple";
           dragging.price = 3;
           dragging.drag = true;
       }
    }

    // Get the star money
    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        for (int i = 0; i < 3; i++) {
            if (money[i].yes) {
                if (logic_mouse_x > money[i].x - 0.5f && logic_mouse_x < money[i].x + 0.5f &&
                    logic_mouse_y < money[i].y + 0.5f && logic_mouse_y > money[i].y - 0.5f) {
                    money[i].yes = false;
                    star_money += 1;
                }
            }
        }
    }

    // Erase a gun
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        for (int i = 0; i < 9; i++) {
            if (logic_mouse_x > table[i].x - (square_length / 2) && logic_mouse_x < table[i].x + (square_length / 2) &&
                logic_mouse_y  < table[i].y + (square_length / 2) && logic_mouse_y  > table[i].y - (square_length / 2)) {  
                table[i].erase = true;
                table[i].life -= 1;
            }
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    sx = window->GetResolution().x / logicSpace.width;
    sy = window->GetResolution().y / logicSpace.height;

    logic_mouse_x = mouseX / sx;
    logic_mouse_y = (window->GetResolution().y - mouseY) / sy;

    // Drop the gun
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        for (int i = 0; i < 9; i++) {
            if (logic_mouse_x > table[i].x - (square_length / 2) && logic_mouse_x < table[i].x + (square_length / 2) &&
                logic_mouse_y  < table[i].y + (square_length / 2) && logic_mouse_y  > table[i].y - (square_length / 2)) {
                if (dragging.price <= star_money && dragging.drag) {
                    table[i].occupated = true;
                    table[i].color = dragging.color;
                    star_money -= dragging.price;                    
                }
            }
        }
        dragging.drag = false;
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}
