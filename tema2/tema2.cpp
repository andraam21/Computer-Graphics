#include "lab_m1/tema2/tema2.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;



Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    // Game init
    {
        endGame = 100.0f;
        score = 0;
        colors[0] = glm::vec3(0.2f, 0.3f, 0.2f);
        colors[1] = glm::vec3(0.3f, 0.3f, 0.2f);
        colors[2] = glm::vec3(0.2f, 0.3f, 0.3f);
    }

    // Tank
    {
        tank.pos = glm::vec3(0, 0, 0);
        tank.angle = 0;
        tank.direction = 0;
        tank.lives = 4;
        tank.rad = 2.5f;
        tank.scl = glm::vec3(0.5f);
        tank.wait = 0.0f;

    }

    // Buildings
    for (int i = 0; i < 5; i++) {
        Building b;
        int sign = rand() % 2;
        b.angle = RADIANS((rand() % 1) * 90);
        b.scl = glm::vec3(0.5f);    
        if (b.angle == 0) {
            b.lat_x = 35 * b.scl.x / 2;
            b.lat_z = 15 * b.scl.x / 2;
            
        } else {
            b.lat_x = 15 * b.scl.x / 2;
            b.lat_z = 35 * b.scl.x / 2;
        }
        b.color = colors[rand() % 3];
        b.pos = glm::vec3(rand() % 40 * pow(-1, sign), -0.5f, rand() % 40 * pow(-1, sign));

        // Override of buildings
        for (int k = 0; k < builds.size(); k++) {
            while (abs(builds[k].pos.x - b.pos.x) < builds[k].lat_x + b.lat_x && abs(builds[k].pos.z - b.pos.z) < builds[k].lat_z + b.lat_z) {
                b.pos += glm::vec3(rand() % 25, 0, rand() % 25);
            }
        }

        // Override with the tank
        while (abs(tank.pos.x - b.pos.x) < tank.rad * 3 + b.lat_x && abs(tank.pos.z - b.pos.z) < tank.rad * 3 + b.lat_z) {
            b.pos += glm::vec3(rand() % 25, 0, rand() % 25);
        }

        builds.push_back(b);
    }

    // Enemies
    for (int i = 0; i < 10; i++) {
        Enemy e;
        int sign = rand() % 2;
        e.timer = 0;
        e.lives = 4;
        e.speed = 1;
        e.color = colors[rand() % 3] + glm::vec3(0.1f, 0.2f, 0.1f);
        e.rad = 2.5f;
        e.angle = 0;
        e.direction = 0;
        e.wait = 0;
        e.move = 0;
        e.pos = glm::vec3(rand() % 40 * pow(-1, sign), 0, rand() % 40 * pow(-1, sign));

        // Override of buildings
        for (int k = 0; k < builds.size(); k++) {
            while (abs(builds[k].pos.x - e.pos.x) < builds[k].lat_x + e.rad && abs(builds[k].pos.z - e.pos.z) < builds[k].lat_z + e.rad) {
                e.pos += glm::vec3(rand() % 25, 0, rand() % 25);
            }
        }

        // Override of enemies
        for (int k = 0; k < enemies.size(); k++) {
            while (abs(enemies[k].pos.x - e.pos.x) < enemies[k].rad + e.rad && abs(enemies[k].pos.z - e.pos.z) < enemies[k].rad + e.rad) {
                e.pos += glm::vec3(rand() % 25, 0, rand() % 25);
            }
        }

        enemies.push_back(e);
    }
   

    // Camera
    {
        camera = new implemented::Camera_Tank();

        aspectRatio = window->props.aspectRatio;
        projectionMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);
    }

    // Mesh for building
    {
        Mesh* mesh = new Mesh("building");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "cottage.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
   

    // Meshes for tank
    {
        Mesh* mesh = new Mesh("down");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "down.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("upper");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "upper.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("cilinder");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "cilinder.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("left");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "left.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("right");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "right.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Mesh for projectile
    {
        Mesh* mesh = new Mesh("projectile");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Mesh for ground
    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "terrain.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader *shader = new Shader("Shader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Light & material properties
    {
        lightPosition = tank.pos + glm::vec3(0, 1, 0);
        materialShininess = 30;
        materialKd = 0.5;
        materialKs = 0.5;
    }
}


void Tema2::FrameStart()
{
    // Clears the color buffer and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{

    // Render ground
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(10, 1.5f, 18));
        RenderSimpleMesh(meshes["plane"], shaders["Shader"], modelMatrix, glm::vec3(0.30f, 0.25f, 0.2f));
    }

    // Render building
    {
        for (int i = 0; i < builds.size(); i++) {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, builds[i].pos) * glm::rotate(modelMatrix, builds[i].angle, glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, builds[i].scl);
            RenderSimpleMesh(meshes["building"], shaders["Shader"], modelMatrix, builds[i].color);  

            // Collision tank - buildings
            float dist_x = tank.rad + builds[i].lat_x;
            float dist_z = tank.rad + builds[i].lat_z;
            if (abs(tank.pos.x - builds[i].pos.x) < dist_x && (abs(tank.pos.z - builds[i].pos.z)) < dist_z) {            
                float p = min(dist_x - abs(tank.pos.x - builds[i].pos.x), dist_z - abs(tank.pos.z - builds[i].pos.z));
                glm::vec3 dif = p * normalize(glm::vec3((tank.pos.x - builds[i].pos.x), 0, (tank.pos.z - builds[i].pos.z)));
                tank.pos += dif;
                camera->position += dif;
            }

            // Collision enemies - buildings
            for (int j = 0; j < enemies.size(); j++) {
                float dist_x = enemies[j].rad + builds[i].lat_x;
                float dist_z = enemies[j].rad + builds[i].lat_z;
                if (abs(enemies[j].pos.x - builds[i].pos.x) < dist_x && (abs(enemies[j].pos.z - builds[i].pos.z)) < dist_z) {
                    float p = min(dist_x - abs(enemies[j].pos.x - builds[i].pos.x), dist_z - abs(enemies[j].pos.z - builds[i].pos.z));
                    glm::vec3 dif = p * normalize(glm::vec3((enemies[j].pos.x - builds[i].pos.x), 0, (enemies[j].pos.z - builds[i].pos.z)));
                    enemies[j].pos += dif;
                }
            }
            
        }
    }

    // Render enemies
    {
        for (int i = 0; i < enemies.size(); i++) {

            if (enemies[i].lives > 0) {
                // Move the enemies            
                enemies[i].timer += deltaTimeSeconds;
                enemies[i].wait += deltaTimeSeconds;

                if (enemies[i].timer >= 5) {
                    enemies[i].timer = 0;
                    enemies[i].move = rand() % 6;
                }

                switch (enemies[i].move) {
                case 0:
                    enemies[i].pos -= glm::vec3(deltaTimeSeconds * sin(enemies[i].angle) * enemies[i].speed, 0, deltaTimeSeconds * cos(enemies[i].angle) * enemies[i].speed);
                    break;
                case 1:
                    enemies[i].angle += -0.5f * deltaTimeSeconds * enemies[i].speed;
                    break;
                case 2:
                    enemies[i].angle += 0.5f * deltaTimeSeconds * enemies[i].speed;
                    break;
                case 3:
                    enemies[i].pos += glm::vec3(deltaTimeSeconds * sin(enemies[i].angle) * enemies[i].speed, 0, deltaTimeSeconds * cos(enemies[i].angle) * enemies[i].speed);
                    break;
                case 4:
                    enemies[i].direction += -0.5f * deltaTimeSeconds * enemies[i].speed;
                    break;
                case 5:
                    enemies[i].direction += 0.5f * deltaTimeSeconds * enemies[i].speed;
                    break;
                }
               
            }
                        
            glm::mat4 modelMatrix;

            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, enemies[i].pos) * glm::rotate(modelMatrix, enemies[i].angle, glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f) - (glm::vec3(4 - enemies[i].lives) * glm::vec3(-0.07f, 0.03f, -0.07f)));
            RenderSimpleMesh(meshes["down"], shaders["Shader"], modelMatrix, enemies[i].color - glm::vec3(4 - enemies[i].lives) * glm::vec3(0.1f, 0.1f, 0.1f));

            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, enemies[i].pos) * glm::rotate(modelMatrix, enemies[i].direction, glm::vec3(0, 1, 0)) * glm::rotate(modelMatrix, enemies[i].angle, glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f) - (glm::vec3(4 - enemies[i].lives) * glm::vec3(-0.07f, 0.03f, -0.07f)));
            RenderSimpleMesh(meshes["upper"], shaders["Shader"], modelMatrix, enemies[i].color - glm::vec3(4 - enemies[i].lives) * glm::vec3(0.1f, 0.1f, 0.1f));

            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, enemies[i].pos) * glm::rotate(modelMatrix, enemies[i].angle, glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f) - (glm::vec3(4 - enemies[i].lives) * glm::vec3(-0.07f, 0.03f, -0.07f)));
            RenderSimpleMesh(meshes["left"], shaders["Shader"], modelMatrix, glm::vec3(0.5f, 0.6f, 0.5f) - glm::vec3(4 - enemies[i].lives) * glm::vec3(0.1f, 0.1f, 0.1f));

            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, enemies[i].pos) * glm::rotate(modelMatrix, enemies[i].angle, glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f) - (glm::vec3(4 - enemies[i].lives) * glm::vec3(-0.07f, 0.03f, -0.07f)));
            RenderSimpleMesh(meshes["right"], shaders["Shader"], modelMatrix, glm::vec3(0.5f, 0.6f, 0.5f) - glm::vec3(4 - enemies[i].lives) * glm::vec3(0.1f, 0.1f, 0.1f));

            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, enemies[i].pos) * glm::rotate(modelMatrix, enemies[i].direction, glm::vec3(0, 1, 0)) * glm::rotate(modelMatrix, enemies[i].angle, glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f) - (glm::vec3(4 - enemies[i].lives) * glm::vec3(-0.07f, 0.03f, -0.07f)));
            RenderSimpleMesh(meshes["cilinder"], shaders["Shader"], modelMatrix, glm::vec3(0.5f, 0.6f, 0.5f) - glm::vec3(4 - enemies[i].lives) * glm::vec3(0.1f, 0.1f, 0.1f));

            // Collision tank - enemies
            if (sqrt(pow(tank.pos.x - enemies[i].pos.x, 2) + pow(tank.pos.z - enemies[i].pos.z, 2)) < tank.rad + enemies[i].rad) {
                float p = tank.rad + enemies[i].rad - sqrt(pow(tank.pos.x - enemies[i].pos.x, 2) + pow(tank.pos.z - enemies[i].pos.z, 2));
                glm::vec3 dif = p * normalize(glm::vec3((tank.pos.x - enemies[i].pos.x), 0, (tank.pos.z - enemies[i].pos.z)));
                tank.pos += 0.5f * dif;
                enemies[i].pos -= 0.5f * dif;
                camera->position += 0.5f * dif;
            }

            // Collision enemies - enemies
            for (int j = 0; j < enemies.size(); j++) {
                if (i != j) {
                    if (sqrt(pow(enemies[j].pos.x - enemies[i].pos.x, 2) + pow(enemies[j].pos.z - enemies[i].pos.z, 2)) < enemies[j].rad + enemies[i].rad) {
                        float p = enemies[j].rad + enemies[i].rad - sqrt(pow(enemies[j].pos.x - enemies[i].pos.x, 2) + pow(enemies[j].pos.z - enemies[i].pos.z, 2));
                        glm::vec3 dif = p * normalize(glm::vec3((enemies[j].pos.x - enemies[i].pos.x), 0, (enemies[j].pos.z - enemies[i].pos.z)));
                        enemies[j].pos += 0.5f * dif;
                        enemies[i].pos -= 0.5f * dif;
                    }
                }
                
            }

            // Attack
            if (enemies[i].wait > 5) {
                Projectile p;
                p.time = 0;
                p.direction = enemies[i].direction + enemies[i].angle;
                p.pos = enemies[i].pos + glm::vec3(sin(p.direction) * 3.5f, 0.9f, cos(p.direction) * 3.5f);
                enemies[i].pros.push_back(p);
                enemies[i].wait = 0;
            }
            

            // Render enemies projectiles
            for (int k = 0; k < enemies[i].pros.size(); k++) {
                
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, enemies[i].pros[k].pos);
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
                RenderSimpleMesh(meshes["projectile"], shaders["Shader"], modelMatrix, glm::vec3(0, 0, 0));

                enemies[i].pros[k].time += deltaTimeSeconds;
                enemies[i].pros[k].pos += glm::vec3(1.5f * deltaTimeSeconds * 3 * sin(enemies[i].pros[k].direction), 0, 1.5f * deltaTimeSeconds * 3 * cos(enemies[i].pros[k].direction));

                // Attack the tank
                if (abs(tank.pos.x - enemies[i].pros[k].pos.x) < tank.rad && abs(tank.pos.z - enemies[i].pros[k].pos.z) < tank.rad) {
                    if (tank.lives > 0) {
                        tank.lives -= 1;
                        enemies[i].pros[k].time += 4;
                    }
                }

                // Collision projectile - buildings
                for (int m = 0; m < builds.size(); m++) {
                    if (abs(builds[m].pos.x - enemies[i].pros[k].pos.x) < builds[m].lat_x && abs(builds[m].pos.z - enemies[i].pros[k].pos.z) < builds[m].lat_z) {
                        enemies[i].pros[k].time += 4;
                    }
                }

                // Collision projectile - tanks
                for (int m = 0; m < enemies.size(); m++) {
                    if (i != m) {
                        if (abs(enemies[m].pos.x - enemies[i].pros[k].pos.x) < enemies[i].rad && abs(enemies[m].pos.z - enemies[i].pros[k].pos.z) < enemies[i].rad) {
                            enemies[i].pros[k].time += 4;
                        }
                    }
                }

                // Time limit
                if (enemies[i].pros[k].time > 4) {
                    enemies[i].pros.erase(enemies[i].pros.begin() + k);
                }
            }
            
        }
    }

    // Render tank
    {
        glm::mat4 modelMatrix;

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, tank.pos) * glm::rotate(modelMatrix, tank.angle, glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, tank.scl - (glm::vec3(4 - tank.lives) * glm::vec3(-0.07f, 0.03f, -0.07f)));
        RenderSimpleMesh(meshes["down"], shaders["Shader"], modelMatrix, glm::vec3(0.22f, 0.3f, 0.45f) - glm::vec3(4 - tank.lives) * glm::vec3(0.05f, 0.05f, 0.05f ));

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, tank.pos) * glm::rotate(modelMatrix, RADIANS(180), glm::vec3(0, 1, 0)) * glm::rotate(modelMatrix, tank.direction, glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, tank.angle, glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, tank.scl - (glm::vec3(4 - tank.lives) * glm::vec3(-0.07f, 0.03f, -0.07f)));
        RenderSimpleMesh(meshes["upper"], shaders["Shader"], modelMatrix, glm::vec3(0.2f, 0.3f, 0.45f) - glm::vec3(4 - tank.lives) * glm::vec3(0.05f, 0.05f, 0.05f));

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, tank.pos) * glm::rotate(modelMatrix, tank.angle, glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, tank.scl - (glm::vec3(4 - tank.lives) * glm::vec3(-0.07f, 0.03f, -0.07f)));
        RenderSimpleMesh(meshes["left"], shaders["Shader"], modelMatrix, glm::vec3(0.5f, 0.6f, 0.7f) - glm::vec3(4 - tank.lives) * glm::vec3(0.1f, 0.1f, 0.1f));

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, tank.pos) * glm::rotate(modelMatrix, tank.angle, glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, tank.scl - (glm::vec3(4 - tank.lives) * glm::vec3(-0.07f, 0.03f, -0.07f)));
        RenderSimpleMesh(meshes["right"], shaders["Shader"], modelMatrix, glm::vec3(0.5f, 0.6f, 0.7f) - glm::vec3(4 - tank.lives) * glm::vec3(0.1f, 0.1f, 0.1f));

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, tank.pos) * glm::rotate(modelMatrix, RADIANS(180), glm::vec3(0, 1, 0)) * glm::rotate(modelMatrix, tank.direction, glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, tank.angle, glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, tank.scl - (glm::vec3(4 - tank.lives) * glm::vec3(-0.07f, 0.03f, -0.07f)));
        RenderSimpleMesh(meshes["cilinder"], shaders["Shader"], modelMatrix, glm::vec3(0.5f, 0.6f, 0.7f) - glm::vec3(4 - tank.lives) * glm::vec3(0.15f, 0.15f, 0.15f));
    }

    // Render projectile
    {
        for (int i = 0; i < tank.pros.size(); i++) {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, tank.pros[i].pos);
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
            RenderSimpleMesh(meshes["projectile"], shaders["Shader"], modelMatrix, glm::vec3(0, 0, 0));

            // Collision projectile - buildings
            for (int k = 0; k < builds.size(); k++) {
                if (abs(builds[k].pos.x - tank.pros[i].pos.x) < builds[k].lat_x && abs(builds[k].pos.z - tank.pros[i].pos.z) < builds[k].lat_z) {
                    tank.pros[i].time += 4;
                }
            }

            // Collision projectile - tanks
            for (int k = 0; k < enemies.size(); k++) {
                if (abs(enemies[k].pos.x - tank.pros[i].pos.x) < tank.rad && abs(enemies[k].pos.z - tank.pros[i].pos.z) < tank.rad) {
                    tank.pros[i].time += 4;
                    if (enemies[k].lives > 0) {
                        enemies[k].lives -= 1;
                    }
                    
                }
            }

            // Time limit
            if (tank.pros[i].time > 4) {
                tank.pros.erase(tank.pros.begin() + i);
            }
        }
    }

    // Render the point light in the scene
    {
        lightPosition = tank.pos + glm::vec3(-1.5f * sin(tank.angle), 7.5f, -1.5f * cos(tank.angle));
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, lightPosition);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(6));
        RenderMesh(meshes["sphere"], shaders["Simple"], modelMatrix);
    }

    // End of the game and display the score
    {
        endGame -= deltaTimeSeconds;
        if (endGame < 0) {

            for (int i = 0; i < enemies.size(); i++) {
                if (enemies[i].lives <= 0) {
                    score += 5;
                }
            }
            cout << "The score is " << score;
            endGame = 100.0f;
        }
    }
}


void Tema2::FrameEnd()
{
  
}


void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Set shader uniforms for light & material properties
    GLint loc_light_position = glGetUniformLocation(shader->program, "light_position");
    glUniform3fv(loc_light_position, 1, glm::value_ptr(lightPosition));
    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();

    // Set eye position uniform
    GLint loc_eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3fv(loc_eye_position, 1, glm::value_ptr(eyePosition));

    // Set material property uniforms (shininess, kd, ks, object color)
    GLint loc_shine = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(loc_shine, materialShininess);

    GLint loc_kd = glGetUniformLocation(shader->program, "material_kd");  
    glUniform1f(loc_kd, materialKd);

    GLint loc_ks = glGetUniformLocation(shader->program, "material_ks");  
    glUniform1f(loc_ks, materialKs);

    GLint loc_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(loc_color, 1, glm::value_ptr(color));

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = camera->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    float cameraSpeed = 3.0f;

    // Move the tank
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT) && tank.lives > 0)
    {
        if (window->KeyHold(GLFW_KEY_W)) {
            tank.pos -= glm::vec3(deltaTime * cameraSpeed * sin(tank.angle), 0, deltaTime * cameraSpeed * cos(tank.angle));
            camera->MoveForward(cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            tank.angle += 1.5f * deltaTime * cameraSpeed;
            camera->RotateThirdPerson_OY(+1.5f * deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            tank.pos += glm::vec3(deltaTime * cameraSpeed * sin(tank.angle), 0, deltaTime * cameraSpeed * cos(tank.angle));
            camera->MoveForward(-cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            tank.angle += -1.5f * deltaTime * cameraSpeed;
            camera->RotateThirdPerson_OY(-1.5f * deltaTime * cameraSpeed);
        }
    }
    else {

        if (window->KeyHold(GLFW_KEY_A)) {
            camera->RotateThirdPerson_OY(1.5f * deltaTime);
        }
       
        if (window->KeyHold(GLFW_KEY_D)) {
            camera->RotateThirdPerson_OY(-1.5f * deltaTime);
        }
    }

    // Move the projectiles
    for (int i = 0; i < tank.pros.size(); i++) {
        tank.pros[i].time += deltaTime;
        tank.pros[i].pos += glm::vec3(-1.5f * deltaTime * cameraSpeed * sin(tank.pros[i].direction), 0, -1.5f * deltaTime * cameraSpeed * cos(tank.pros[i].direction));
    }

    // Timer the projectile delay
    {
        tank.wait += deltaTime;
    }
    

}


void Tema2::OnKeyPress(int key, int mods)
{
}


void Tema2::OnKeyRelease(int key, int mods)
{
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
   // Move the cilinder of the tank
    mouseY = window->GetResolution().y - mouseY;
    
    if (mouseX < window->GetResolution().x / 2) {
        mouseX = mouseX - (window->GetResolution().x / 2);
    } else {
        mouseX = mouseX % (window->GetResolution().x / 2);
    }

    if (mouseY < window->GetResolution().y / 2) {
        mouseY = mouseY - (window->GetResolution().y / 2);
    } else {
        mouseY = mouseY % (window->GetResolution().y / 2);
    }

    float complement;
    if (mouseY > 0) {
        if (mouseX > 0) {
            complement = RADIANS(0);
        } else {
            complement = RADIANS(180);
        }
    } else {
        if (mouseX < 0) {
            complement = RADIANS(180);
        } else {
            complement = RADIANS(360);
        }
    }
    
    tank.direction = -complement + atan((mouseY + 200) / (mouseX + 0.01f)) - RADIANS(90);
    
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Attack
    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT) && tank.wait > 1 && tank.lives > 0) {
        Projectile p;
        p.time = 0;
        p.direction = tank.direction + tank.angle;
        p.pos = tank.pos + glm::vec3(sin(p.direction) * -3.5f, 0.9f, cos(p.direction) * -3.5f);
        tank.pros.push_back(p);

        // Reinitialise the waiting time for projectiles
        tank.wait = 0;
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
