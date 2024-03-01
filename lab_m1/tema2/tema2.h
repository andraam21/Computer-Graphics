#pragma once

#include <vector>

#include "components/simple_scene.h"
#include "components/transform.h"
#include "lab_m1/tema2/camera.h"

using namespace std;


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        Tema2();
        ~Tema2();

        struct Building
        {
            glm::vec3 pos;
            glm::vec3 color;
            float angle;      
            float lat_x;
            float lat_z;
            glm::vec3 scl;
        };

        struct Projectile
        {
            glm::vec3 pos;
            float time;
            float direction;
        };

        struct Enemy
        {
            glm::vec3 pos;
            glm::vec3 color;
            float timer;
            int move;
            float speed;
            int lives;
            float angle;
            float direction;
            float rad;
            float wait;
            vector<Projectile> pros;
        };        

        struct Tank
        {
            glm::vec3 pos;
            glm::vec3 scl;
            int lives;
            float angle;
            float direction;
            float rad;
            float wait;
            vector<Projectile> pros;
        };

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color = glm::vec3(1));
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        Tank tank;
        glm::vec3 lightPosition;
        glm::vec3 eyePosition;
        glm::vec3 color;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;
        vector<Building> builds;
        vector<Enemy> enemies;
        glm::vec3 colors[3];
        float endGame;
        int score;

     protected:
        implemented::Camera_Tank* camera;
        glm::mat4 projectionMatrix;     
        float fov = RADIANS(60);
        float aspectRatio;
        float zNear = 0.01f;
        float zFar = 200.0f;
    };
}   