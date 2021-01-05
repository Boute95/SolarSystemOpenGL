#include <solar/GLManager.hpp>
#include <glimac/FilePath.hpp>
#include <iostream> // std::cerr


///////////////////////////////////////////////////////////////////////////////
solar::GLManager::GLManager() {
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
void solar::GLManager::drawVertices(const GLenum mode, const GLint vertexCount) {
    glDrawArrays(mode, vertexDrawStartIndex, vertexCount);
    vertexDrawStartIndex += vertexCount;
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::addShader(const std::string key, const std::string vs, const std::string fs) {
    if (programs.count(key) == 0) {
        programs[key] = glimac::loadProgram(vs, fs);
    }
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::useShader(const std::string key) {
    if (activeProgram.compare(key) != 0) {
        programs[key].use();
        activeProgram = key;
    }
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::addUniform(std::string id) {
    GLint location = glGetUniformLocation(programs[activeProgram].getGLId(), id.c_str());
    uniforms[id] = location;
}



///////////////////////////////////////////////////////////////////////////////
bool solar::GLManager::hasUniform(std::string id) const {
    return uniforms.count(id);
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::setUniformValue(std::string id, const GLint val) {
    if (!hasUniform(id)) {
        addUniform(id);
    }
    glUniform1i(uniforms[id], val);
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::setUniformValue(std::string id, const float val) {
    if (!hasUniform(id)) {
        addUniform(id);
    }
    glUniform1f(uniforms[id], val);
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::setUniformValue(std::string id, const glm::vec3& v) {
    if (!hasUniform(id)) {
        addUniform(id);
    }
    glUniform3fv(uniforms[id], 1, glm::value_ptr(v));

}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::setUniformValue(std::string id, const glm::mat4& iMat4) {
    if (!hasUniform(id)) {
        addUniform(id);
    }
    glUniformMatrix4fv(uniforms[id], 1, GL_FALSE, glm::value_ptr(iMat4));
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::enableLine() {
    glEnable(GL_LINE_WIDTH);
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::disableLine() {
    glDisable(GL_LINE_WIDTH);
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::setLineWidth(const float w) {
    glLineWidth(w);
}



///////////////////////////////////////////////////////////////////////////////
GLuint solar::GLManager::addTexture(const std::unique_ptr<glimac::Image>& img) {
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GLsizei(img->getWidth()), GLsizei(img->getHeight()), 0, GL_RGBA, GL_FLOAT, img->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    return id;
}



///////////////////////////////////////////////////////////////////////////////
GLuint solar::GLManager::addCubeMapTexture(const std::array<std::unique_ptr<glimac::Image>, 6>& images) {
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);
    for (unsigned int i = 0 ; i < 6 ; i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, GLsizei(images[i]->getWidth()), GLsizei(images[i]->getHeight()), 0, GL_RGBA, GL_FLOAT, images[i]->getPixels());
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    return id;
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::setActiveTexture(const std::string& location, const GLuint id, const GLenum textureUnit, const GLenum textureType) {
    activeTextures.insert(textureUnit);
    glActiveTexture(textureUnit);
    glBindTexture(textureType, id);
    setUniformValue(location, GLint(textureUnit - GL_TEXTURE0));
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::enableDepthWrite() {
    glDepthMask(GL_TRUE);
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::disableDepthWrite() {
    glDepthMask(GL_FALSE);
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::bind() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao);
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::unbind() {
    vertexDrawStartIndex = 0;
    for (auto& texUnit : activeTextures) {
        glActiveTexture(texUnit);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
    glBindVertexArray(0);
}



///////////////////////////////////////////////////////////////////////////////
void solar::GLManager::clear() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}