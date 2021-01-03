#ifndef SOLAR_PHYSICSENGINE_HPP
#define SOLAR_PHYSICSENGINE_HPP

#include <vector>
#include <memory>
#include <solar/Simulable.hpp>

namespace solar {

    class PhysicsEngine {
    
    private:
        std::vector<std::shared_ptr<Simulable>> simulables;
        float timeInHour;

    public:
        void addObject(std::shared_ptr<Simulable> o);
        // void applyTimeFactor(float f);
        void simulate();

    };

}

#endif