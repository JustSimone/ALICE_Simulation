#include "library.h"
#include <iostream>
int main() {
    Particle::AddParticle(PL::PionPlus);
    Particle::AddParticle(PL::Positron);
    Particle::AddParticle(PL::Positron);
    Particle::AddParticle(PL::Electron);
    Particle::AddParticle(PL::Proton);

    Particle particella1("Electron", 1,1,1);
    Particle particella2("Proton",2,3,4);
    Particle particella3("Electron",2,4,5);

    Particle::PrintTable();

    return 0;
}
