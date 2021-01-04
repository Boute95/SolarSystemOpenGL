#ifndef SOLAR_PHYSICSENGINE_HPP
#define SOLAR_PHYSICSENGINE_HPP

#include <vector>
#include <memory>
#include <chrono>
#include <solar/Simulable.hpp>

namespace solar {

    class PhysicsEngine {
    
    private:
        std::vector<std::shared_ptr<Simulable>> simulables;
        double timeInHour;
        double hourPerSecond;
        std::chrono::system_clock::time_point timeLastSimulate;

    public:
        PhysicsEngine();
        void addObject(std::shared_ptr<Simulable> o);
        void setHourPerSecond(const double h);
        void simulate();

    };

}

#endif