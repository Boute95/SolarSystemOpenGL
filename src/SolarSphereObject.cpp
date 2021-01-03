#include <solar/SolarSphereObject.hpp>
#include <iostream> // std::cout

///////////////////////////////////////////////////////////////////////////////
solar::SolarSphereObject::SolarSphereObject(float radiusInKm) 
    : sphere(radiusInKm, 32, 32), vertices(size_t(sphere.getVertexCount())) {
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
glm::mat4 solar::SolarSphereObject::getTransformMatrix() const {
    return transformMatrix;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::setParent(std::shared_ptr<Transformable> p) {
    parent = p;
    // transformMatrix = p->getTransformMatrix();
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::setApoapsis(const float km) {
    apoapsis = km;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::setPeriapsis(const float km) {
    periapsis = km;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::setOrbitalEccentricity(const float e) {
    orbitalEccentricity = e;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::setOrbitalPeriod(const float hours) {
    orbitalPeriod = hours;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::setRotationPeriod(const float hours) {
    rotationPeriod = hours;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::setOrbitalInclination(const float degrees) {
    orbitalInclination = degrees;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::update(const float timeInHour) {
    resetTransforms();
    float theta = float(fmod(timeInHour, 2 * 3.141593f));
    float alpha = (apoapsis + periapsis) / 2;
    float r = (alpha * (1 - orbitalEccentricity * orbitalEccentricity)) / (1 + orbitalEccentricity * float(cos(theta)));
    rotate(theta, glm::vec3(0.f, 0.f, 1.f));
    translate(glm::vec3(0.f, r, 0.f));
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::addColorTexture(const std::string& path) {
    std::unique_ptr<glimac::Image> p_tex = glimac::loadImage(path);
    if (!p_tex) {
        std::cout << "WARNING : Can't load " << path << std::endl;
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