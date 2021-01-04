#include <solar/PhysicsEngine.hpp>

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
void solar::PhysicsEngine::simulate() {
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = now - timeLastSimulate;
    timeLastSimulate = now;
    timeInHour += elapsedSeconds.count() * hourPerSecond;
    for(auto& o : simulables) {
        o->update(timeInHour);
    }
}