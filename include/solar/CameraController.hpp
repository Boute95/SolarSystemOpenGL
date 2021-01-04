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

    public:
        CameraController(const double iAspectRatio);
        void addView(const std::string id, const View& view);
        void switchView(const std::string id);
        const Camera& getCamera() const;
    };

}

#endif
