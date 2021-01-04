#include <solar/View.hpp>

///////////////////////////////////////////////////////////////////////////////
void solar::View::setTrackball(const glm::vec3& iTarget, const double iDistanceFromTarget, const double iAngleX, const double iAngleY) {
    target = iTarget;
    distanceFromTarget = iDistanceFromTarget;
    angleX = iAngleX;
    angleY = iAngleY;
    trackball = true;
}



///////////////////////////////////////////////////////////////////////////////
void solar::View::setFree(const glm::vec3& iTarget, const glm::vec3& iPosition) {
    target = iTarget;
    position = iPosition;
    trackball = false;
}



///////////////////////////////////////////////////////////////////////////////
bool solar::View::isTrackball() const {
    return trackball;
}



///////////////////////////////////////////////////////////////////////////////
glm::vec3 solar::View::getTarget() const {
    return target;
}



///////////////////////////////////////////////////////////////////////////////
glm::vec3 solar::View::getPosition() const {
    return position;
}



///////////////////////////////////////////////////////////////////////////////
double solar::View::getDistanceFromTarget() const {
    return distanceFromTarget;
}



///////////////////////////////////////////////////////////////////////////////
double solar::View::getAngleX() const {
    return angleX;
}



///////////////////////////////////////////////////////////////////////////////
double solar::View::getAngleY() const {
    return angleY;
}