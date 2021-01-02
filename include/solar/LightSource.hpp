#ifndef SOLAR_LIGHTSOURCE_HPP
#define SOLAR_LIGHTSOURCE_HPP

#include <glm/geometric.hpp>

namespace solar {

    class LightSource {

    public:
        virtual ~LightSource() {}
        virtual glm::vec3 getPosition() const = 0;
        virtual float getIntensity() const = 0;
        virtual glm::vec3 getColor() const = 0;

    };

}

#endif