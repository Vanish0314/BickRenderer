/*
 * @Author: Vanish
 * @Date: 2024-09-14 13:51:18
 * @LastEditTime: 2024-09-14 16:04:00
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#include "Camera/Camera.hpp"


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
void Camera::Rotate(const float &yaw, const float &pitch)
{
    glm::mat4 rotationMatrix(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    this->position = glm::vec3(rotationMatrix * glm::vec4(this->position, 1.0f));
}
void Camera::Zoom(const float &zoomFOV)
{
    this->fov += zoomFOV;
}