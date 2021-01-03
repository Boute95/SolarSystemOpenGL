#ifndef SOLAR_ENGINE_HPP
#define SOLAR_ENGINE_HPP

#include <unordered_map>
#include <memory>
#include <solar/SolarSphereObject.hpp>
#include <solar/Star.hpp>
#include <glimac/Program.hpp>

namespace solar {

    class Engine {

    private: 
        std::unordered_map<std::string, std::shared_ptr<SolarSphereObject>> solarObjects;
        std::unordered_map<std::string, std::shared_ptr<Star>> stars;

    public:
        Engine();
        void start(char* appPathStr);
    };
    
    

}

#endif