#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

#include <string>

class ParticleType {
private:
  const std::string fName;
  const double fMass;
  const int fCharge;
public:

  //Constructor
  ParticleType(std::string Name, double Mass, int Charge);

  //Getters
  std::string GetParticleName() const;
  double GetParticleMass() const;
  int GetParticleCharge() const;

  //Printer
  virtual void Print() const;
};

#endif
