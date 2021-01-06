#include <solar/CameraController.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
solar::CameraController::CameraController(const double iAspectRatio) 
: camera(iAspectRatio) {}



///////////////////////////////////////////////////////////////////////////////
void solar::CameraController::setView(const std::string id, const View& view) {
    views[id] = view;
}



///////////////////////////////////////////////////////////////////////////////
void solar::CameraController::switchView(const std::string id) {
    if (views.count(id) == 0) {
        std::cout << "In solar::CameraController::switchView() : Unknown view id, can't change camera settings" << std::endl;
        return;
    }
    currentView = id;
    totalZoom = 0;
    if(views[id].isTrackball()) {
        camera.resetTransforms();
        camera.translate(views[id].getTarget());
        camera.translate(glm::vec3(0.f, 0.f, views[id].getDistanceFromTarget()));
        camera.rotate(static_cast<float>(views[id].getAngleX() * M_PI / 180.), glm::vec3(0.0f, 1.0f, 0.0f));
        camera.rotate(static_cast<float>(views[id].getAngleY() * M_PI / 180.), glm::vec3(1.0f, 0.0f, 0.0f));
    } else {
        std::cout << "In solar::CameraController::switchView() : Free view is not implemented yet" << std::endl;
    }
}



///////////////////////////////////////////////////////////////////////////////
std::string solar::CameraController::getCurrentView() const {
    return currentView;
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
void solar::CameraController::zoom(const double iZoom) {
    totalZoom += iZoom;
    if(views[currentView].isTrackball()) {
        glm::vec3 s;
        glm::quat q;
        glm::vec3 t;
        glm::vec3 skew;
        glm::vec4 p;
        glm::decompose(camera.getTransformMatrix(), s, q, t, skew, p);
        camera.resetTransforms();
        camera.translate(views[currentView].getTarget());
        camera.translate(glm::vec3(0.f, 0.f, views[currentView].getDistanceFromTarget() + totalZoom));
        camera.rotate(q);
    } else {
        std::cout << "In solar::CameraController::switchView() : Free view is not implemented yet" << std::endl;
    }
}



///////////////////////////////////////////////////////////////////////////////
const solar::Camera& solar::CameraController::getCamera() const {
    return camera;
}