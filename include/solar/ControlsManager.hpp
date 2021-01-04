#ifndef SOLAR_CONTROLSMANAGER_HPP
#define SOLAR_CONTROLSMANAGER_HPP

#include <solar/CameraController.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <glm/geometric.hpp>

namespace solar {

    class ControlsManager {

    private:
        glm::ivec2 lastMousePosition;


    public:
        ControlsManager();
        void update(SDL_Event& e, const glimac::SDLWindowManager& winManager, CameraController& camController);

    };

}

#endif