#include <iostream>

#include <string>
#include "ResonanceType.hpp"

//Class ResonanceType
//----------------------
//Constructor
ResonanceType::ResonanceType(std::string Name, double Mass, int Charge, double Width):
ParticleType(Name, Mass, Charge),
fWidth(Width)
{}

//Getter
double ResonanceType::GetParticleRW() const { return fWidth; }

//Printer
void ResonanceType::Print() const {
  ParticleType::Print();
  std::cout << "Width of the Particle's Resonance: "<< fWidth << '\n';
}
//----------------------
