#ifndef SOLAR_ENGINE_HPP
#define SOLAR_ENGINE_HPP

#include <unordered_map>
#include <memory>
#include <solar/SolarSphere.hpp>
#include <solar/RenderEngine.hpp>
#include <solar/PhysicsEngine.hpp>
#include <glimac/Program.hpp>

namespace solar {

    class Engine {

    private: 
        std::unordered_map<std::string, std::shared_ptr<SolarSphere>> solarObjects;

        void initObjects(const glimac::FilePath& appPath, RenderEngine& renderEngine, PhysicsEngine& physicsEngine);

    public:
        Engine();
        void start(char* appPathStr);
    };
    
    

}

#endif