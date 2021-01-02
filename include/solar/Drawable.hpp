#ifndef SOLAR_DRAWABLE_HPP
#define SOLAR_DRAWABLE_HPP

#include <glimac/common.hpp>
#include <solar/GLManager.hpp>

namespace solar {

    class Drawable {

    public:
        virtual ~Drawable() {}
        virtual void draw(GLManager& glManager) = 0;
        virtual const std::vector<glimac::ShapeVertex>& getVertices() = 0;
        
    };

}

#endif