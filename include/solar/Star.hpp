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
    double intensity;

    public:
        Star(const double radiusInKm, const glm::vec3& iColor, const double iIntensity);
        virtual glm::vec3 getPosition() const override;
        virtual glm::vec3 getColor() const override;
        virtual double getIntensity() const override;

    };

}

#endif