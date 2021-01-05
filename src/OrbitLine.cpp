#include <solar/OrbitLine.hpp>

///////////////////////////////////////////////////////////////////////////////
solar::OrbitLine::OrbitLine(glm::vec3 iColor, float iThickness, std::shared_ptr<SolarSphere> p)
    : SolarSphereDecorator(p), color(iColor), thickness(iThickness) {
        
}



///////////////////////////////////////////////////////////////////////////////
void solar::OrbitLine::draw() {
    SolarSphereDecorator::draw();
    glManager->setUniformValue("uUseTexture", 0);
    glManager->setUniformValue("uColor", color);
    glManager->setUniformValue("uUseModelMatrix", 0);
    glManager->setLineWidth(thickness);
    glManager->drawVertices(GL_LINE_STRIP, GLint(orbitVertices.size()));
    glManager->setUniformValue("uUseTexture", 1);
    glManager->setUniformValue("uUseModelMatrix", 1);
}



///////////////////////////////////////////////////////////////////////////////
const std::vector<glimac::ShapeVertex>& solar::OrbitLine::getVertices() {
    if (allVertices.size() == 0) {
        if (apoapsis && periapsis) {
            orbitVertices = getOrbitVertices(64);
            allVertices.insert(allVertices.end(), SolarSphereDecorator::getVertices().begin(), SolarSphereDecorator::getVertices().end());
            allVertices.insert(allVertices.end(), orbitVertices.begin(), orbitVertices.end());
            return allVertices;
        } else {
            return SolarSphereDecorator::getVertices();
        }
    } else {
        return allVertices;
    }
}



///////////////////////////////////////////////////////////////////////////////
void solar::OrbitLine::setGLManager(std::shared_ptr<GLManager> g) {
    glManager = g;
    SolarSphereDecorator::setGLManager(g);
}



///////////////////////////////////////////////////////////////////////////////
void solar::OrbitLine::setApoapsis(const double km) {
    SolarSphereDecorator::setApoapsis(km);
    apoapsis = km;
}



///////////////////////////////////////////////////////////////////////////////
void solar::OrbitLine::setPeriapsis(const double km) {
    SolarSphereDecorator::setPeriapsis(km);
    periapsis = km;
}



///////////////////////////////////////////////////////////////////////////////
void solar::OrbitLine::setOrbitalEccentricity(const double e) {
    SolarSphereDecorator::setOrbitalEccentricity(e);
    orbitalEccentricity = e;
}



///////////////////////////////////////////////////////////////////////////////
std::vector<glimac::ShapeVertex> solar::OrbitLine::getOrbitVertices(size_t vertexCount) const {
    std::vector<glimac::ShapeVertex> arr(vertexCount);
    double theta = 0.;
    double thetaIncr =  (2 * M_PI) / static_cast<double>(vertexCount-1);
    for (size_t i = 0 ; i < vertexCount-1 ; i++) {
        double alpha = (apoapsis + periapsis) / 2;
        double r = (alpha * (1 - orbitalEccentricity * orbitalEccentricity)) / (1 + orbitalEccentricity * cos(theta));
        double x = r * cos(theta);
        double y = r * sin(theta);
        arr[i].position = glm::vec3(x, 0., y);
        arr[i].normal = glm::vec3(0.f, 0.f, 1.f);
        theta += thetaIncr;
    }
    arr[vertexCount-1].position = arr[0].position;
    arr[vertexCount-1].normal = arr[0].position;
    return arr;
}
