#include <solar/PhysicsEngine.hpp>

///////////////////////////////////////////////////////////////////////////////
void solar::PhysicsEngine::addObject(std::shared_ptr<Simulable> o) {
    simulables.push_back(o);
    timeInHour = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/1e6));

}



///////////////////////////////////////////////////////////////////////////////
void solar::PhysicsEngine::simulate() {
    timeInHour += 10;
    for(auto& o : simulables) {
        o->update(timeInHour);
    }
}