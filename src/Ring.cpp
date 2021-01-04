#include <solar/Ring.hpp>

///////////////////////////////////////////////////////////////////////////////
solar::Ring::Ring(std::shared_ptr<solar::SolarSphere> iSolarSphere) 
    : SolarSphereDecorator(iSolarSphere) {}