#include <solar/SolarSphereBase.hpp>
#include <iostream> // std::cout

///////////////////////////////////////////////////////////////////////////////
solar::SolarSphereBase::SolarSphereBase(double radiusInKm) 
    : sphere(static_cast<float>(radiusInKm), 32, 32), vertices(size_t(sphere.getVertexCount())), transformMatrix(1.f) {
    auto p = sphere.getDataPointer();
    for (size_t i = 0 ; i < size_t(sphere.getVertexCount()) ; i++) {
        vertices[i] = p[i];
    }
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereBase::translate(const glm::vec3& v) {
    transformMatrix = glm::translate(transformMatrix, v);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereBase::rotate(const float angle, const glm::vec3& axis) {
    transformMatrix = glm::rotate(transformMatrix, angle, axis);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereBase::scale(const glm::vec3& v) {
    transformMatrix = glm::scale(transformMatrix, v);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereBase::resetTransforms() {
    transformMatrix = glm::mat4(1.f);
}



///////////////////////////////////////////////////////////////////////////////
glm::vec3 solar::SolarSphereBase::getWorldPosition() const {
    glm::vec4 v = transformMatrix * glm::vec4(0.f, 0.f, 0.f, 1.f);
    return glm::vec3(v.x, v.y, v.z);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereBase::setParent(std::shared_ptr<Transformable> p) {
    parent = p;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereBase::setApoapsis(const double km) {
    apoapsis = km;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereBase::setPeriapsis(const double km) {
    periapsis = km;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereBase::setOrbitalEccentricity(const double e) {
    orbitalEccentricity = e;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereBase::setOrbitalPeriod(const double hours) {
    orbitalPeriod = hours;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereBase::setRotationPeriod(const double hours) {
    rotationPeriod = hours;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereBase::setOrbitalInclination(const double degrees) {
    orbitalInclination = degrees;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereBase::update(const double timeInHour) {
    resetTransforms();
    double theta = fmod(timeInHour, orbitalPeriod) * 2 * M_PI / orbitalPeriod;
    double alpha = (apoapsis + periapsis) / 2;
    double r = (alpha * (1 - orbitalEccentricity * orbitalEccentricity)) / (1 + orbitalEccentricity * cos(theta));
    double x = r * cos(theta);
    double y = r * sin(theta);
    translate(glm::vec3(x, 0.f, y));
    double selfRotation = fmod(timeInHour, rotationPeriod) * 2 * M_PI / rotationPeriod;
    rotate(static_cast<float>(selfRotation), glm::vec3(0.f, 1.f, 0.f));
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereBase::addColorTexture(const std::string& path) {
    std::unique_ptr<glimac::Image> p_tex = glimac::loadImage(path);
    if (!p_tex) {
        std::cout << "WARNING : Can't load " << path << std::endl;
        return;
    }
    colorTexture = glManager->addTexture(p_tex);
}



///////////////////////////////////////////////////////////////////////////////
 void solar::SolarSphereBase::setGLManager(std::shared_ptr<GLManager> iGLManager) {
     glManager = iGLManager;
 }



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereBase::draw() {
    glManager->setUniformValue("uUseTexture", 1);
    glManager->setUniformValue("uUseModelMatrix", 1);
    glManager->setUniformValue("uModelMatrix", transformMatrix);
    glManager->setActiveTexture("uColorTexture", colorTexture);
    glManager->drawVertices(GL_TRIANGLES, GLint(vertices.size()));
}



///////////////////////////////////////////////////////////////////////////////
const std::vector<glimac::ShapeVertex>& solar::SolarSphereBase::getVertices() {
    return vertices;
}