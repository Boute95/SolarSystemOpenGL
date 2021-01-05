#include <solar/SolarSphereDecorator.hpp>

///////////////////////////////////////////////////////////////////////////////
solar::SolarSphereDecorator::SolarSphereDecorator(std::shared_ptr<solar::SolarSphere> iSolarSphere) :
    base(iSolarSphere) {}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereDecorator::draw() {
    base->draw();
}



///////////////////////////////////////////////////////////////////////////////
const std::vector<glimac::ShapeVertex>& solar::SolarSphereDecorator::getVertices() {
    return base->getVertices();
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereDecorator::setGLManager(std::shared_ptr<solar::GLManager> iManager) {
    base->setGLManager(iManager);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereDecorator::translate(const glm::vec3& v) {
    base->translate(v);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereDecorator::rotate(const float angle, const glm::vec3& axis) {
    base->rotate(angle, axis);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereDecorator::rotate(const glm::quat& q) {
    base->rotate(q);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereDecorator::scale(const glm::vec3& v) {
    base->scale(v);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereDecorator::resetTransforms() {
    base->resetTransforms();
}



///////////////////////////////////////////////////////////////////////////////
glm::mat4 solar::SolarSphereDecorator::getTransformMatrix() const {
    return base->getTransformMatrix();
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereDecorator::setParent(std::shared_ptr<solar::Transformable> t) {
    base->setParent(t);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereDecorator::setApoapsis(const double km) {
    base->setApoapsis(km);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereDecorator::setPeriapsis(const double km) {
    base->setPeriapsis(km);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereDecorator::setOrbitalEccentricity(const double e) {
    base->setOrbitalEccentricity(e);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereDecorator::setOrbitalPeriod(const double hours) {
    base->setOrbitalPeriod(hours);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereDecorator::setRotationPeriod(const double hours) {
    base->setRotationPeriod(hours);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereDecorator::setOrbitalInclination(const double degrees) {
    base->setOrbitalInclination(degrees);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereDecorator::update(const double timeInHour) {
    base->update(timeInHour);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereDecorator::addColorTexture(const std::string& path) {
    base->addColorTexture(path);
}


