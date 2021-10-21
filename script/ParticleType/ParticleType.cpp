#include <iostream>
#include <string>
#include "ParticleType.hpp"

//Class ParticleType
//----------------------
//Constructor
ParticleType::ParticleType(std::string Name, double Mass, int Charge):
fName(Name),
fMass(Mass),
fCharge(Charge)
{}

//Getters
std::string ParticleType::GetParticleName() const { return fName; }
double ParticleType::GetParticleMass() const { return fMass; }
int ParticleType::GetParticleCharge() const { return fCharge; }
double ParticleType::GetParticleWidth() const { return 0; }


//Printer
void ParticleType::Print() const {
  std::cout << "Particle's Name: "<<fName << '\n';
  std::cout << "Particle's Mass: "<<fMass << '\n';
  std::cout << "Particle's Charge: "<<fCharge << '\n';
  std::cout << "-------------------------------------" << '\n';
}
//----------------------
