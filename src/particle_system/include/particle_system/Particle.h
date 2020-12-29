#pragma once

namespace particlesystem {
    
struct Particle {
    double x;
    double y;
public:
    Particle();
    void updateParticlePosition(double x, double y) {this->x = x ; this->y = y;};
};

} // namespace particlesystem
