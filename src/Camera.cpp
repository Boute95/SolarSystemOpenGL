#include <solar/Camera.hpp>
#include <glimac/SDLWindowManager.hpp>


///////////////////////////////////////////////////////////////////////////////
solar::Camera::Camera(double iAspectRatio) : aspectRatio(iAspectRatio), transformMatrix() {}



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
    transformMatrix = glm::mat4();
}



///////////////////////////////////////////////////////////////////////////////
glm::vec3 solar::Camera::getWorldPosition() const {
    auto translateCol = glm::column(transformMatrix, 3);
    return glm::vec3(translateCol.x, translateCol.y, translateCol.z);
}



///////////////////////////////////////////////////////////////////////////////
glm::mat4 solar::Camera::getProjMatrix() const {
    return glm::perspective(50.f, static_cast<float>(aspectRatio), static_cast<float>(1e5), static_cast<float>(1e11));
}



///////////////////////////////////////////////////////////////////////////////
glm::mat4 solar::Camera::getViewMatrix() const {
    return transformMatrix;
}

