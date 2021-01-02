#include <solar/SolarSphereObject.hpp>

///////////////////////////////////////////////////////////////////////////////
solar::SolarSphereObject::SolarSphereObject(float radiusInKm) 
    : sphere(radiusInKm, 64, 64), vertices(size_t(sphere.getVertexCount())) {
    auto p = sphere.getDataPointer();
    for (size_t i = 0 ; i < size_t(sphere.getVertexCount()) ; i++) {
        vertices[i] = p[i];
    }
}



///////////////////////////////////////////////////////////////////////////////
void solar::SolarSphereObject::draw(solar::GLManager& glManager) {
    glManager.drawVertices(GLint(vertices.size()));
}



///////////////////////////////////////////////////////////////////////////////
const std::vector<glimac::ShapeVertex>& solar::SolarSphereObject::getVertices() {
    return vertices;
}