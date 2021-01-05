#ifndef SOLAR_TRANSFORMABLE_HPP
#define SOLAR_TRANSFORMABLE_HPP

#include <glm/glm.hpp>

namespace solar {

    class Transformable {

    public:
        virtual ~Transformable() {}
        virtual void translate(const glm::vec3&) = 0;
        virtual void rotate(const float angle, const glm::vec3& axis) = 0;
        virtual void scale(const glm::vec3&) = 0;
        virtual void resetTransforms() = 0;
        virtual glm::vec3 getWorldPosition() const = 0;

    };

}

#endif