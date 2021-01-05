#ifndef SOLAR_DRAWABLE_HPP
#define SOLAR_DRAWABLE_HPP

#include <glimac/common.hpp>
#include <solar/GLManager.hpp>

namespace solar {

    class Drawable {

    public:
        virtual ~Drawable() {}
        virtual void draw(const glm::mat4& projMatrix, const glm::mat4& viewMatrix) = 0;
        virtual const std::vector<glimac::ShapeVertex>& getVertices() = 0;
        virtual void setGLManager(std::shared_ptr<GLManager>) = 0;
        virtual void setShader(const std::string vs, const std::string fs) = 0;
        
    };

}

#endif