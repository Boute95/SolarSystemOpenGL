#ifndef SOLAR_CAMERACONTROLLER_HPP
#define SOLAR_CAMERACONTROLLER_HPP

#include <solar/Camera.hpp>
#include <solar/View.hpp>
#include <map>
#include <memory>

namespace solar {

    class CameraController {

    private:
        Camera camera;
        std::map<std::string, View> views;
        std::string currentView;
        double totalZoom;

    public:
        CameraController(const double iAspectRatio);
        void setView(const std::string id, const View& view);
        void switchView(const std::string id);
        std::string getCurrentView() const;
        void rotateLeft(const double degrees);
        void rotateUp(const double degrees);
        void zoom(const double iZoom);
        const Camera& getCamera() const;
    };

}

#endif
