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
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0));
    glManager->setActiveTexture("uColorTexture", colorTexture);
    glManager->setUniformValue("uModelMatrix", modelMatrix);
    glManager->drawVertices(GLint(vertices.size()));
}



///////////////////////////////////////////////////////////////////////////////
const std::vector<glimac::ShapeVertex>& solar::SolarSphereObject::getVertices() {
    return vertices;
}