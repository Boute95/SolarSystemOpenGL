#include <solar/PhysicsEngine.hpp>

///////////////////////////////////////////////////////////////////////////////
void solar::PhysicsEngine::addObject(std::shared_ptr<Simulable> o) {
    simulables.push_back(o);
}



///////////////////////////////////////////////////////////////////////////////
void solar::PhysicsEngine::simulate() {
    timeInHour += 0.01;
    for(auto& o : simulables) {
        o->update(timeInHour);
    }
}