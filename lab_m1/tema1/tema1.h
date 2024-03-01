#pragma once

#include "components/simple_scene.h"
#include <iostream>
#include <map>
#include <string>

using namespace std;


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

        struct Star
        {
            float x;
            float y;
            float rot;
            bool yes;
            string color;
        };

        struct Table
        {
            bool erase;
            bool occupated;
            string color;
            float x;
            float y;
            float radius;
            int star_count;
            int life;
            float scale;
            float shoot_time;
            Star bullets[5];
        };

        struct Enemy
        {
            float x;
            float y;
            bool move;
            int life;
            float scale;
            string color;
        };

        struct Drag
        {
            bool drag;
            string color;
            int price;

        };

        struct Money
        {
            bool yes;
            float x;
            float y;
            float rot;
        };

     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawScene(glm::mat3 visMatrix);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

        glm::mat3 VisualizationTransf2D(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);

        void SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

     protected:
        float sx = 0, sy = 0;
        float logic_mouse_x = 0, logic_mouse_y = 0;
        float square_length = 1;
        float square_life_length = 0.7f;
        float rect_len = 0.7f, rect_hei = 3.6f;
        float ind = 0.2f, rad = 0.314f;
        int number_of_life = 3;
        int star_money = 5;
        float random = 0;
        float pos_enemy = 12;
        float frame = 0;
        string random_colors[4] = {"orange", "blue", "yellow", "purple"};
        Drag dragging;
        Table table[9];
        Enemy enemies[3];
        Money money[3];
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 modelMatrix, visMatrix;
        glm::vec3 corner = glm::vec3(0.001, 0.001, 0);
    };
}   
