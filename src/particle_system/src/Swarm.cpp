#include <particle_system/Swarm.h>

namespace particlesystem {

Swarm::Swarm () {

    particles_ = new Particle[NPARTICLES];

}

Swarm::~Swarm () {
    delete[] particles_;
}

} // namespace particlesystem