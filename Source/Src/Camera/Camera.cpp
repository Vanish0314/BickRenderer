/*
 * @Author: Vanish
 * @Date: 2024-09-14 13:51:18
 * @LastEditTime: 2024-10-19 19:48:17
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#include "Camera/Camera.hpp"

std::shared_ptr<Camera> Camera::main = nullptr;

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(position, position + forward, up);
}
glm::mat4 Camera::GetProjectionMatrix() const
{
    return glm::perspective(glm::radians(fov), aspectRatio, nearZ, farZ);
}
void Camera::SetPosition(const glm::vec3 &position)
{
    this->position = position;
}
void Camera::SetForward(const glm::vec3 &forward)
{
    this->forward = forward;
    this->right = glm::normalize(glm::cross(forward, up));
}
void Camera::Move(const glm::vec3 &moveDirAndDist)
{
    this->position += moveDirAndDist;
}
void Camera::Rotate(const float &yawOffset, const float &pitchOffset) {
    // 累积旋转角度
    this->yaw += yawOffset;
    this->pitch += pitchOffset;

    // 限制俯仰角度
    if (this->pitch > 89.0f) this->pitch = 89.0f;
    if (this->pitch < -89.0f) this->pitch = -89.0f;

    // 计算新的方向向量
    glm::vec3 direction;
    direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    direction.y = sin(glm::radians(this->pitch));
    direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->forward = glm::normalize(direction);
    
    // 更新右向量和上向量
    this->right = glm::normalize(glm::cross(this->forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    this->up = glm::normalize(glm::cross(this->right, this->forward));
}
void Camera::Zoom(const float &zoomFOV)
{
    this->fov += zoomFOV;
}