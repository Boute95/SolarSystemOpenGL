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
        virtual void setApoapsis(const double km) = 0;
        virtual void setPeriapsis(const double km) = 0;
        virtual void setOrbitalEccentricity(const double) = 0;
        virtual void setOrbitalPeriod(const double hours) = 0;
        virtual void setRotationPeriod(const double hours) = 0;
        virtual void setOrbitalInclination(const double degrees) = 0;
        virtual void update(const double timeInHour) = 0;

    };

}

#endif
