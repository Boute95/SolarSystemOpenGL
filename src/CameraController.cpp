#include <solar/CameraController.hpp>
#include <glm/geometric.hpp>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
solar::CameraController::CameraController(const double iAspectRatio) : camera(iAspectRatio) {}



///////////////////////////////////////////////////////////////////////////////
void solar::CameraController::addView(const std::string id, const View& view) {
    views[id] = view;
}



///////////////////////////////////////////////////////////////////////////////
void solar::CameraController::switchView(const std::string id) {
    if (views.count(id) == 0) {
        std::cout << "In solar::CameraController::switchView() : Unknown view id, can't change camera settings" << std::endl;
        return;
    }
    if(views[id].isTrackball()) {
        camera.resetTransforms();
        camera.translate(glm::vec3(0.f, 0.f, views[id].getDistanceFromTarget()));
        camera.rotate(static_cast<float>(views[id].getAngleX() * M_PI / 180.), glm::vec3(0.0f, 1.0f, 0.0f));
        camera.rotate(static_cast<float>(views[id].getAngleY() * M_PI / 180.), glm::vec3(1.0f, 0.0f, 0.0f));
    } else {
        std::cout << "In solar::CameraController::switchView() : Free view is not implemented yet" << std::endl;
    }
}



///////////////////////////////////////////////////////////////////////////////
void solar::CameraController::rotateLeft(const double degrees) {
    camera.rotate(static_cast<float>(degrees * M_PI / 180.), glm::vec3(0.0f, 1.0f, 0.0f));
}



///////////////////////////////////////////////////////////////////////////////
void solar::CameraController::rotateUp(const double degrees) {
    camera.rotate(static_cast<float>(degrees * M_PI / 180.), glm::vec3(1.0f, 0.0f, 0.0f));
}



///////////////////////////////////////////////////////////////////////////////
const solar::Camera& solar::CameraController::getCamera() const {
    return camera;
}