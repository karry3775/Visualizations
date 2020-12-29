#pragma once

#include <particle_system/Particle.h>

namespace particlesystem {

class Swarm {
public:
    const static int NPARTICLES = 500;
private:
    Particle* particles_;
public:
    Swarm();
    virtual ~Swarm();

    Particle* getParticles() const { return particles_;};

};


} // namespace particlesystem