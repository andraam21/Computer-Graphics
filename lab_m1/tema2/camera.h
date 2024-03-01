#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"


namespace implemented
{
    class Camera_Tank
    {
    public:
        Camera_Tank()
        {
            position = glm::vec3(0, 2.25f, 5.5f);
            forward = glm::vec3(0, 0, -1);
            up = glm::vec3(0, 1, 0);
            right = glm::vec3(1, 0, 0);
            distanceToTarget = 5.5f;
        }

        Camera_Tank(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
        {
            Set(position, center, up);
        }

        ~Camera_Tank()
        { 
        }
  
        void Set(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
        {
            this->position = position;
            forward = glm::normalize(center - position);
            right = glm::cross(forward, up);
            this->up = glm::cross(right, forward);
        }

        void MoveForward(float distance)
        {
            glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
            position += dir * distance;
        }

        void TranslateForward(float distance)
        {
            position += glm::normalize(forward) * distance;
        }

        void TranslateUpward(float distance)
        {
            position += glm::normalize(up) * distance;
        }

        void TranslateRight(float distance)
        {
            position += glm::normalize(right) * distance;
        }

        void RotateFirstPerson_OX(float angle)
        {
            glm::mat4 rotation = glm::rotate(glm::mat4(1), angle, right);
            forward = normalize(rotation * glm::vec4(forward, 0));
            right = normalize(rotation * glm::vec4(right, 0));
            up = normalize(glm::cross(right, forward));

        }

        void RotateFirstPerson_OY(float angle)
        {
            glm::mat4 rotation = glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0));
            forward = normalize(rotation * glm::vec4(forward, 0));
            right = normalize(rotation * glm::vec4(right, 0));
            up = normalize(glm::cross(right, forward));
        }

        void RotateFirstPerson_OZ(float angle)
        {
            glm::mat4 rotation = glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0));
            up = normalize(rotation * glm::vec4(up, 0));
            right = normalize(rotation * glm::vec4(right, 0));
            forward = normalize(cross(up, right));

        }

        void RotateThirdPerson_OX(float angle)
        {
            TranslateForward(distanceToTarget);
            RotateFirstPerson_OX(angle);
            TranslateForward(-distanceToTarget);
        }

        void RotateThirdPerson_OY(float angle)
        {
            TranslateForward(distanceToTarget);
            RotateFirstPerson_OY(angle);
            TranslateForward(-distanceToTarget);
        }

        void RotateThirdPerson_OZ(float angle)
        {
            TranslateForward(distanceToTarget);
            RotateFirstPerson_OZ(angle);
            TranslateForward(-distanceToTarget);
        }

        glm::mat4 GetViewMatrix()
        {
            return glm::lookAt(position, position + forward, up);
        }

        glm::vec3 GetTargetPosition()
        {
            return position + forward * distanceToTarget;
        }

    public:
        float distanceToTarget;
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;
    };
}
