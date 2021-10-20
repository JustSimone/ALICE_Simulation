#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP

#include <string>
#include "ParticleType.h"

class ResonanceType: public ParticleType {
private:
  const double fWidth;
public:

  //Constructor
  ResonanceType(std::string Name, double Mass, int Charge, double Width);

  //Pritner
  void Print() const;

  //Getter
  double GetParticleRW() const;
};

#endif
