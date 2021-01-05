#ifndef SOLAR_GLMANAGER_HPP
#define SOLAR_GLMANAGER_HPP

#include <vector>
#include <map>
#include <set>
#include <memory>
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>

namespace solar {

    class GLManager {

    private:
        std::map<std::string, glimac::Program> programs;
        std::string activeProgram;
        std::vector<glimac::ShapeVertex> vertices;
        std::map<std::string, GLint> uniforms;
        std::set<GLenum> activeTextures;
        GLint vertexDrawStartIndex;
        GLuint vbo;
        GLuint vao;

    public:
        GLManager();
        void addVertices(const std::vector<glimac::ShapeVertex>& v);
        void drawVertices(const GLenum mode, const GLint vertexCount);
        void addShader(const std::string key, const std::string vs, const std::string fs);
        void useShader(const std::string key);
        void addUniform(std::string id);
        // void deleteUniform(std::string id);
        bool hasUniform(std::string id) const;
        void setUniformValue(std::string id, const GLint);
        void setUniformValue(std::string id, const float);
        // void setUniformValue(std::string id, const glm::vec2&);
        void setUniformValue(std::string id, const glm::vec3&);
        // void setUniformValue(std::string id, const glm::vec4&);
        // void setUniformValue(std::string id, const glm::mat3&);
        void setUniformValue(std::string id, const glm::mat4&);
        void setLineWidth(const float w);
        GLuint addTexture(const std::unique_ptr<glimac::Image>& img);
        GLuint addCubeMapTexture(const std::array<std::unique_ptr<glimac::Image>, 6>& images);
        void setActiveTexture(const std::string& location, const GLuint id, const GLenum textureUnit = GL_TEXTURE0, const GLenum textureType = GL_TEXTURE_2D);
        void enableLine();
        void disableLine();
        void enableDepthWrite();
        void disableDepthWrite();
        void bind();
        void unbind();
        void clear();

    };

}


#endif