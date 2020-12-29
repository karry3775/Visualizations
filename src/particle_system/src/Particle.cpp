#include <stdlib.h>
#include <particle_system/Particle.h>


namespace particlesystem {

Particle::Particle() {

    x = ( rand() / (RAND_MAX + 1.0) ) ; // generate a random floating point between 0 and 1
    y = ( rand() / (RAND_MAX + 1.0) ) ;
}

} // namespace particlesystem
