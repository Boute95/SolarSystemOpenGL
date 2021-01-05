#include <solar/ControlsManager.hpp>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
solar::ControlsManager::ControlsManager() : lastMousePosition(-1.) {}


///////////////////////////////////////////////////////////////////////////////
void solar::ControlsManager::update(SDL_Event& e, const glimac::SDLWindowManager& winManager, CameraController& camController) {

    if(e.type == SDL_MOUSEMOTION && winManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
        glm::ivec2 newMousePosition = winManager.getMousePosition();
        if (lastMousePosition.x == -1 && lastMousePosition.y == -1) {
            lastMousePosition = newMousePosition;
        }
        glm::ivec2 deltaMousePosition{newMousePosition - lastMousePosition};
        camController.rotateLeft(deltaMousePosition.x * 1);
        camController.rotateUp(deltaMousePosition.y * 1);
        lastMousePosition = newMousePosition;
        
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.button == SDL_BUTTON_WHEELDOWN) {
            camController.zoom(-1e8);
        } else if (e.button.button == SDL_BUTTON_WHEELUP) {
            camController.zoom(1e8);
        }
        
    }

}