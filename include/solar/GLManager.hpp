#ifndef SOLAR_GLMANAGER_HPP
#define SOLAR_GLMANAGER_HPP

#include <vector>
#include <map>
#include <GL/glew.h>
#include <glimac/common.hpp>

namespace solar {

    class GLManager {

    private:
        std::vector<glimac::ShapeVertex> vertices;
        std::map<std::string, GLint> uniforms;
        GLint vertexDrawStartIndex;
        GLuint vob;
        GLuint vao;

    public:
        void addVertices(const std::vector<glimac::ShapeVertex>& v);
        void drawVertices(const GLint vertexCount);
        // void addUniform(std::string id);
        // void deleteUniform(std::string id);
        // bool hasUniform() const;
        // void setUniformValue(std::string id, const GLuint);
        // void setUniformValue(std::string id, const glm::vec2&);
        // void setUniformValue(std::string id, const glm::vec3&);
        // void setUniformValue(std::string id, const glm::vec4&);
        // void setUniformValue(std::string id, const glm::mat3&);
        // void setUniformValue(std::string id, const glm::mat4&);
        void bind();
        void unbind();

    };

}


#endif