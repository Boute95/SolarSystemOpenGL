#include <solar/Camera.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <glm/gtc/matrix_transform.hpp>


///////////////////////////////////////////////////////////////////////////////
solar::Camera::Camera(double iAspectRatio) 
: aspectRatio(iAspectRatio), transformMatrix(1.f) {}



///////////////////////////////////////////////////////////////////////////////
void solar::Camera::translate(const glm::vec3& v) {
    transformMatrix = glm::translate(transformMatrix, v);
}



///////////////////////////////////////////////////////////////////////////////
void solar::Camera::rotate(const float angle, const glm::vec3& axis) {
    transformMatrix = glm::rotate(transformMatrix, angle, axis);
}



///////////////////////////////////////////////////////////////////////////////
void solar::Camera::scale(const glm::vec3& v) {
    transformMatrix = glm::scale(transformMatrix, v);
}



///////////////////////////////////////////////////////////////////////////////
void solar::Camera::resetTransforms() {
    transformMatrix = glm::mat4(1.f);
}



///////////////////////////////////////////////////////////////////////////////
glm::vec3 solar::Camera::getWorldPosition() const {
    glm::vec4 v = transformMatrix * glm::vec4(0.f, 0.f, 0.f, 1.f);
    return glm::vec3(v.x, v.y, v.z);
}



///////////////////////////////////////////////////////////////////////////////
glm::mat4 solar::Camera::getProjMatrix() const {
    return glm::perspective(glm::radians(50.f), static_cast<float>(aspectRatio), static_cast<float>(1e5), static_cast<float>(1e11));
}



///////////////////////////////////////////////////////////////////////////////
glm::mat4 solar::Camera::getViewMatrix() const {
    return transformMatrix;
}

