#ifndef SOLAR_SIMULABLE_HPP
#define SOLAR_SIMULABLE_HPP

#include <glm/geometric.hpp>
#include <solar/Transformable.hpp>
#include <memory>

namespace solar {

    class Simulable : public Transformable {

    public:
        virtual ~Simulable() {}
        virtual void setParent(std::shared_ptr<Transformable>) = 0;
        virtual void setApoapsis(const float km) = 0;
        virtual void setPeriapsis(const float km) = 0;
        virtual void setOrbitalEccentricity(const float) = 0;
        virtual void setOrbitalPeriod(const float hours) = 0;
        virtual void setRotationPeriod(const float hours) = 0;
        virtual void setOrbitalInclination(const float degrees) = 0;
        virtual void update(const float timeInHour) = 0;

    };

}

#endif
