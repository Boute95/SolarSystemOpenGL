#ifndef SOLAR_SOLARSPHERE_HPP
#define SOLAR_SOLARSPHERE_HPP

#include <solar/Drawable.hpp>
#include <solar/Simulable.hpp>

namespace solar {

    class SolarSphere : public Drawable, public Simulable {
    
    public:
        virtual ~SolarSphere() {}
        virtual void addColorTexture(const std::string& path) = 0;

    };

}

#endif