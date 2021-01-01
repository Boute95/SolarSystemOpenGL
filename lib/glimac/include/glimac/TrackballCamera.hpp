#pragma once

#include "common.hpp"

namespace glimac {

    class TrackballCamera {

    public:
        TrackballCamera();
        void moveFront(const float delta);
        void rotateLeft(const float degrees);
        void rotateUp(const float degrees);
        glm::mat4 getViewMatrix() const;

    private:
        float m_fDistance;
        float m_fAngleX;
        float m_fAngleY;
    };

}