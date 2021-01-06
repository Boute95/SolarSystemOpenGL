#include <solar/PhysicsEngine.hpp>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
solar::PhysicsEngine::PhysicsEngine() : hourPerSecond(1) {}



///////////////////////////////////////////////////////////////////////////////
void solar::PhysicsEngine::addObject(std::shared_ptr<Simulable> o) {
    simulables.push_back(o);
    timeInHour = rand() / (RAND_MAX/1e6);
}



///////////////////////////////////////////////////////////////////////////////
void solar::PhysicsEngine::setHourPerSecond(const double h) {
    hourPerSecond = h;
}



///////////////////////////////////////////////////////////////////////////////
double solar::PhysicsEngine::getHourPerSecond() const {
    return hourPerSecond;
}



///////////////////////////////////////////////////////////////////////////////
void solar::PhysicsEngine::simulate() {
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = now - timeLastSimulate;
    timeLastSimulate = now;
    timeInHour += elapsedSeconds.count() * hourPerSecond;
    for(auto& o : simulables) {
        o->update(timeInHour);
    }
}