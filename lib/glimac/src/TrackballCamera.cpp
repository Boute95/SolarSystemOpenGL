#include <glimac/TrackballCamera.hpp>

///////////////////////////////////////////////////////////////////////////////
glimac::TrackballCamera::TrackballCamera() : m_fDistance(-5.f), m_fAngleX(0.f), m_fAngleY(0.f) {}


///////////////////////////////////////////////////////////////////////////////
void glimac::TrackballCamera::moveFront(const float delta) { 
    m_fDistance += delta;
    if (m_fDistance < 0) {
        m_fDistance = 0;
    }
}


///////////////////////////////////////////////////////////////////////////////
void glimac::TrackballCamera::rotateLeft(const float degrees) { m_fAngleX += degrees; }


///////////////////////////////////////////////////////////////////////////////
void glimac::TrackballCamera::rotateUp(const float degrees) { m_fAngleY += degrees; }


///////////////////////////////////////////////////////////////////////////////
glm::mat4 glimac::TrackballCamera::getViewMatrix() const {
    glm::mat4 mat = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, m_fDistance));
    mat = glm::rotate(mat, glm::radians(m_fAngleX), glm::vec3(0.0f, 1.0f, 0.0f));
    mat = glm::rotate(mat, glm::radians(m_fAngleY), glm::vec3(1.0f, 0.0f, 0.0f));
    return mat;
}