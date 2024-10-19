/*
 * @Author: Vanish
 * @Date: 2024-09-14 13:51:13
 * @LastEditTime: 2024-10-19 19:48:34
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#pragma once

#include <memory>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
public:
    static std::shared_ptr<Camera> main;

public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

    int imgWidth, imgHeight;
    double fov;
    double nearZ = 0.1, farZ = 1000.0;
    double aspectRatio;

    float yaw = -90.0f, pitch = 0.0f;
public:
    Camera(const int &width, const int &height,const int &fov,const bool &isMain = true)
    {
        imgWidth = width;
        imgHeight = height;
        this->fov = fov;

        aspectRatio = (double)imgWidth / (double)imgHeight;

        if(main == nullptr && isMain)
        {
            main = std::shared_ptr<Camera>(this);
        }
    }
    ~Camera() {}

public:
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

public:
    void SetPosition(const glm::vec3 &pos);
    void SetForward(const glm::vec3 &forward);

public:
    float speed = 3.0f;
    void Move(const glm::vec3 &moveDirAndDist);
    void Rotate(const float &yaw, const float &pitch);
    void Zoom(const float &zoomFOV);

};
