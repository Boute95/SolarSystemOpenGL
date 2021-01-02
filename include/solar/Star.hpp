#ifndef SOLAR_STAR_HPP
#define SOLAR_STAR_HPP

#include <glm/geometric.hpp>
#include <solar/LightSource.hpp>
#include <solar/SolarSphereObject.hpp>

namespace solar {

    class Star : public LightSource, public SolarSphereObject {

    private:
    glm::vec3 position;
    glm::vec3 color;
    float intensity;

    public:
        Star(const float radiusInKm, const glm::vec3& iColor, const float iIntensity);
        virtual glm::vec3 getPosition() const override;
        virtual glm::vec3 getColor() const override;
        virtual float getIntensity() const override;

    };

}

#endif