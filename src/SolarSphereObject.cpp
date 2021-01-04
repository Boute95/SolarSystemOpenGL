#include <solar/SolarSphereObject.hpp>
#include <iostream> // std::cout

#define PI 3.14159265358979323846

///////////////////////////////////////////////////////////////////////////////
solar::SolarSphereObject::SolarSphereObject(double radiusInKm) 
    : sphere(static_cast<float>(radiusInKm), 32, 32), vertices(size_t(sphere.getVertexCount())) {
    auto p = sphere.getDataPointer();
    for (size_t i = 0 ; i < size_t(sphere.getVertexCount()) ; i++) {
        vertices[i] = p[i];
    }
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::translate(const glm::vec3& v) {
    transformMatrix = glm::translate(transformMatrix, v);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::rotate(const float angle, const glm::vec3& axis) {
    transformMatrix = glm::rotate(transformMatrix, angle, axis);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::scale(const glm::vec3& v) {
    transformMatrix = glm::scale(transformMatrix, v);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::resetTransforms() {
    transformMatrix = glm::mat4();
}



///////////////////////////////////////////////////////////////////////////////
glm::vec3 solar::SolarSphereObject::getWorldPosition() const {
    auto translateCol = glm::column(transformMatrix, 3);
    return glm::vec3(translateCol.x, translateCol.y, translateCol.z);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::setParent(std::shared_ptr<Transformable> p) {
    parent = p;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::setApoapsis(const double km) {
    apoapsis = km;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::setPeriapsis(const double km) {
    periapsis = km;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::setOrbitalEccentricity(const double e) {
    orbitalEccentricity = e;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::setOrbitalPeriod(const double hours) {
    orbitalPeriod = hours;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::setRotationPeriod(const double hours) {
    rotationPeriod = hours;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::setOrbitalInclination(const double degrees) {
    orbitalInclination = degrees;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::update(const double timeInHour) {
    resetTransforms();
    double theta = fmod(timeInHour, orbitalPeriod) * 2 * PI / orbitalPeriod;
    double alpha = (apoapsis + periapsis) / 2;
    double r = (alpha * (1 - orbitalEccentricity * orbitalEccentricity)) / (1 + orbitalEccentricity * cos(theta));
    // rotate(static_cast<float>(theta), glm::vec3(0.f, 0.f, 1.f));
    double x = r * cos(theta);
    double y = r * sin(theta);
    translate(glm::vec3(x, 0.f, y));
    double selfRotation = fmod(timeInHour, rotationPeriod) * 2 * PI / rotationPeriod;
    rotate(static_cast<float>(selfRotation), glm::vec3(0.f, 1.f, 0.f));
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::addColorTexture(const std::string& path) {
    std::unique_ptr<glimac::Image> p_tex = glimac::loadImage(path);
    if (!p_tex) {
        std::cout << "WARNING : Can't load " << path << std::endl;
        return;
    }
    colorTexture = glManager->addTexture(p_tex);
}



///////////////////////////////////////////////////////////////////////////////
 void solar::SolarSphereObject::setGLManager(std::shared_ptr<GLManager> iGLManager) {
     glManager = iGLManager;
 }



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::draw() {
    glManager->setUniformValue("uModelMatrix", transformMatrix);
    glManager->setActiveTexture("uColorTexture", colorTexture);
    glManager->drawVertices(GLint(vertices.size()));
}



///////////////////////////////////////////////////////////////////////////////
const std::vector<glimac::ShapeVertex>& solar::SolarSphereObject::getVertices() {
    return vertices;
}