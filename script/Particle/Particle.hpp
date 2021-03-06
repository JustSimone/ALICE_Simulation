
#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <string>
#include <vector>
#include "../ParticleType/ParticleType.hpp"

enum class PL{Electron, Positron, Proton, Antiproton, PionPlus, PionMinus, Pion0, KaonPlus, KaonMinus, Kaon0};

class Particle {
private:
  double fPx;
  double fPy;
  double fPz;

  static const int fMaxNumParticleType = 10;
  static ParticleType* fParticleType[fMaxNumParticleType];
  static int fNParticleType;
  int fIndex;

  static int FindParticle(std::string PTBF); //Particle To Be Found

  void Boost(double bx, double by, double bz);

public:

  Particle(std::string name, double Px, double Py, double Pz);
  Particle() = default;
  static void AddParticle(std::string name , double mass , int charge , double with=0);
  static void AddParticle(PL particle);

  int GetIndex() const;
  int GetCharge() const;
  std::string GetName() const;
  double GetPx() const;
  double GetPy() const;
  double GetPz() const;
  double GetMass() const;
  double GetMomentum() const;
  double GetTotalEnergy() const;
  double GetInvMass(Particle& p) const;
  double GetTrasMomentum() const;

  void SetIndex(std::string);
  void SetIndex(int index);
  void SetMomentum(double x, double y, double z);

  static void PrintTable();
  void PrintParticle() const;

  static void ParticleFeatures(PL& particle, int const N);

  int Decay2body(Particle &dau1,Particle &dau2) const;


};

#endif
