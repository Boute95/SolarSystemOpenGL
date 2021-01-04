#ifndef SOLAR_RING_HPP
#define SOLAR_RING_HPP

#include <solar/SolarSphereDecorator.hpp>

namespace solar {

    class Ring : public SolarSphereDecorator {
    
    public:
        Ring(std::shared_ptr<SolarSphere>);

    };

}

#endif