#include <solar/GLManager.hpp>
#include <glimac/FilePath.hpp>
#include <iostream> // std::cerr


///////////////////////////////////////////////////////////////////////////////
solar::GLManager::GLManager(const glimac::Program& p) : program(p) {
    glEnable(GL_DEPTH_TEST);
    // VBO
    glGenBuffers(1, &vbo);
    // VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    const GLuint VERTEX_ATTR_POSITION = 1;
    const GLuint VERTEX_ATTR_NORMAL = 2;
    const GLuint VERTEX_ATTR_TEX = 3;
    const GLuint VERTEX_ATTR_STRIDE = sizeof(glimac::ShapeVertex);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, VERTEX_ATTR_STRIDE, (const void*) offsetof(glimac::ShapeVertex, position));
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, VERTEX_ATTR_STRIDE, (const void*) offsetof(glimac::ShapeVertex, normal));
    glEnableVertexAttribArray(VERTEX_ATTR_TEX);
    glVertexAttribPointer(VERTEX_ATTR_TEX, 2, GL_FLOAT, GL_FALSE, VERTEX_ATTR_STRIDE, (const void*) offsetof(glimac::ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::addVertices(const std::vector<glimac::ShapeVertex>& v) {
    vertices.insert(vertices.end(), v.begin(), v.end());
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(vertices.size() * sizeof(glimac::ShapeVertex)), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::drawVertices(const GLint vertexCount) {
    glDrawArrays(GL_TRIANGLES, vertexDrawStartIndex, vertexCount);
    vertexDrawStartIndex += vertexCount;
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::addUniform(std::string id) {
    GLint location = glGetUniformLocation(program.getGLId(), id.c_str());
    uniforms[id] = location;
}



///////////////////////////////////////////////////////////////////////////////
bool solar::GLManager::hasUniform(std::string id) const {
    return uniforms.count(id);
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::setUniformValue(std::string id, const glm::mat4& iMat4) {
    if (!hasUniform(id)) {
        addUniform(id);
    }
    glUniformMatrix4fv(uniforms[id], 1, GL_FALSE, glm::value_ptr(iMat4));
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::bind() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao);
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::unbind() {
    vertexDrawStartIndex = 0;
    glBindVertexArray(0);
}