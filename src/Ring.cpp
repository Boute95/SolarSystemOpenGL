#include <solar/Ring.hpp>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
solar::Ring::Ring(const double iInnerRadiusInKm, const double iOuterRadiusInKm, std::shared_ptr<solar::SolarSphere> iSolarSphere) 
    : SolarSphereDecorator(iSolarSphere), innerRadiusInKm(iInnerRadiusInKm), outerRadiusInKm(iOuterRadiusInKm) {}



///////////////////////////////////////////////////////////////////////////////
std::vector<glimac::ShapeVertex> solar::Ring::getAnnulusVertices(const double innerR, const double outerR, const unsigned int iterationCount) const {
    std::vector<glimac::ShapeVertex> arr(iterationCount * 2 + 1);
    double theta = 0.f;
    double thetaIncr = 360. / iterationCount * 2.;
    constexpr double radianCoef = M_PI / 180;
    for(size_t i = 0 ; i < iterationCount ; ++i) {
        arr[i * 2].position = glm::vec3(innerR * glm::cos(radianCoef * theta), 0.f, innerR * glm::sin(radianCoef * theta)); 
        arr[i * 2].normal = glm::vec3(0.f, 0.f, 1.f);
        arr[i * 2].texCoords = glm::vec2(0.f, 0.f);
        theta += thetaIncr;
        arr[i * 2 + 1].position = glm::vec3(outerR * glm::cos(radianCoef * theta), 0.f, outerR * glm::sin(radianCoef * theta)); 
        arr[i * 2 + 1].normal = glm::vec3(0.f, 0.f, 1.f);
        arr[i * 2 + 1].texCoords = glm::vec2(1.f, 0.f);
        theta += thetaIncr;
    }
    arr[iterationCount * 2].position = glm::vec3(innerR * glm::cos(radianCoef * 0.), 0.f,innerR * glm::sin(radianCoef * 0.));
    arr[iterationCount * 2].normal = glm::vec3(0.f, 0.f, 1.f);
    arr[iterationCount * 2].texCoords = glm::vec2(0.f, 0.f);
    return arr;
}



///////////////////////////////////////////////////////////////////////////////
void solar::Ring::draw() {
    SolarSphereDecorator::draw();
    glManager->setActiveTexture("uColorTexture", ringColorTexture);
    glManager->drawVertices(GL_TRIANGLE_STRIP, GLint(ringVertices.size()));
}



///////////////////////////////////////////////////////////////////////////////
const std::vector<glimac::ShapeVertex>& solar::Ring::getVertices() {
    if (allVertices.size() == 0) {
        ringVertices = getAnnulusVertices(innerRadiusInKm, outerRadiusInKm, 64);
        allVertices.insert(allVertices.end(), SolarSphereDecorator::getVertices().begin(), SolarSphereDecorator::getVertices().end());
        allVertices.insert(allVertices.end(), ringVertices.begin(), ringVertices.end());
    }
    return allVertices;
}



///////////////////////////////////////////////////////////////////////////////
void solar::Ring::setGLManager(std::shared_ptr<GLManager> g) {
    glManager = g;
    SolarSphereDecorator::setGLManager(g);
}



///////////////////////////////////////////////////////////////////////////////
void solar::Ring::addRingColorTexture(const std::string& path) {
    std::unique_ptr<glimac::Image> p_tex = glimac::loadImage(path);
    if (!p_tex) {
        std::cout << "WARNING : Can't load " << path << std::endl;
        return;
    }
    ringColorTexture = glManager->addTexture(p_tex);
}



///////////////////////////////////////////////////////////////////////////////
void solar::Ring::addRingTransparencyTexture(const std::string& path) {
    std::unique_ptr<glimac::Image> p_tex = glimac::loadImage(path);
    if (!p_tex) {
        std::cout << "WARNING : Can't load " << path << std::endl;
        return;
    }
    ringTransparencyTexture = glManager->addTexture(p_tex);
}
