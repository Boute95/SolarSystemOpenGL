#include <solar/SolarSphereObject.hpp>

///////////////////////////////////////////////////////////////////////////////
solar::SolarSphereObject::SolarSphereObject(float radiusInKm) 
    : sphere(radiusInKm, 32, 32), vertices(size_t(sphere.getVertexCount())) {
    auto p = sphere.getDataPointer();
    for (size_t i = 0 ; i < size_t(sphere.getVertexCount()) ; i++) {
        vertices[i] = p[i];
    }
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::draw(solar::GLManager& glManager) {
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0));
    glManager.setUniformValue("uModelMatrix", modelMatrix);
    glManager.drawVertices(GLint(vertices.size()));
}



///////////////////////////////////////////////////////////////////////////////
const std::vector<glimac::ShapeVertex>& solar::SolarSphereObject::getVertices() {
    return vertices;
}