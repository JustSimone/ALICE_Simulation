#include "library.h"
#include <string>
#include <iostream>
#include <cmath>

int Particle::fNParticleType = 0;
ParticleType* Particle::fParticleType[fMaxNumParticleType];

// Public Methods
int Particle::FindParticle(std::string PTBF) {
  int i = 0;
  for(; i < fNParticleType; ++i) {
    std::string ParticleName = fParticleType[i]->GetParticleName();
    if(ParticleName == PTBF) { return i; }
    else if (fNParticleType == 0) { return 0; }
  }
  return 10;
}

void Particle::AddParticle(std::string name, double mass, int charge, double width) {
  int const N = fNParticleType;
  int chack = FindParticle(name);
  if(N < fMaxNumParticleType && chack==10) {
    if(width!=0) {
      fParticleType[N] = new ResonanceType(name, mass, charge, width);
      ++fNParticleType;
    } else {
      fParticleType[N] = new ParticleType (name, mass, charge);
      ++fNParticleType;
    }
  } else {
    std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
  }
}

//Costruttore
Particle::Particle(std::string name, double Px = 0, double Py = 0, double Pz = 0):
fPx(Px),
fPy(Py),
fPz(Pz),
fIndex (FindParticle(name))
{}

// Getter Methods
int Particle::GetIndex() const { return fIndex; }
double Particle::GetPx() const { return fPx; }
double Particle::GetPy() const { return fPy; }
double Particle::GetPz() const { return fPz; }
double Particle::GetMass() const {
  return (fParticleType[fIndex]->GetParticleMass());
}
double Particle::GetMomentum() const {
  return fPx*fPx + fPy*fPy + fPz*fPz;
}
double Particle::GetTotalEnergy() const {
  double m = GetMass();
  double p2 = GetMomentum();
  return sqrt(m*m + p2);
}
double Particle::GetInvMass(Particle& p) const {
  double E1 = GetTotalEnergy();
  double E2 = p.GetTotalEnergy();
  double p1 = GetMomentum();
  double p2 = p.GetMomentum();
  double M = sqrt((E1+ E2)*(E1+ E2) - (sqrt(p1)+sqrt(p2))*(sqrt(p1)+sqrt(p2)));
  return M;
}

// Setter Methods
void Particle::SetIndex(std::string type) {
  const int index = FindParticle(type);
  if(10 != index) {
    fIndex = index;
  }
}

void Particle::SetIndex(int index) {
  if(index < fNParticleType) {
    fIndex = index;
  }
}

void Particle::SetMomentum(double x, double y, double z) {
  fPx = x;
  fPy = y;
  fPz = z;
}

//Printer
void Particle::PrintTable() {
  for(int i = 0; i < fNParticleType; ++i) {
    fParticleType[i]->Print();
  }
}

void Particle::PrintParticle() const {
  std::cout << "Particle index: " << fIndex << '\n';
  std::cout << "Particle name: "<< fParticleType[fIndex]->GetParticleName() << '\n';
  std::cout << "Px: "<< fPx << '\n';
  std::cout << "Py: "<< fPy << '\n';
  std::cout << "Pz: "<< fPz << '\n';
  std::cout << "-------------------------------------" << '\n';
}

// ParticleList

void Particle::ParticleFeatures(PL& particle, int const N) {
  int check;
  switch (particle) {
    case (PL::Electron):
      check = FindParticle("Electron");
      if (check == 10) {
        fParticleType[N] = new ParticleType ("Electron", 0.5109, -1);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::Proton) :
      check = FindParticle("Proton");
      if(check == 10) {
        fParticleType[N] = new ParticleType ("Proton", 938.3, +1);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::Positron) :
      check = FindParticle("Positron");
      if(check == 10) {
        fParticleType[N] = new ParticleType ("Positron", 0.5109, +1);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::PionMinus):
      check = FindParticle("Pion-");
      if(check == 10) {
        fParticleType[N] = new ParticleType ("Pion-", 139.6, +1);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::PionPlus) :
      check = FindParticle("Pion+");
      if(check == 10) {
        fParticleType[N] = new ParticleType ("Pion+", 139.6, -1);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::Pion0) :
      check = FindParticle("Pion0");
      if(check == 10) {
        fParticleType[N] = new ParticleType ("Pion0", 135.0, 0);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::KaonPlus) :
      check = FindParticle("Kaon+");
      if(check == 10) {
        fParticleType[N] = new ParticleType ("Kaon+", 493.6, +1);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::KaonMinus) :
      check = FindParticle("Kaon");
      if(check == 10) {
        fParticleType[N] = new ParticleType ("Kaon", 493.6, -1);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::Kaon0) :
      check = FindParticle("Kaon0");
      if(check == 10) {
        fParticleType[N] = new ParticleType ("Kaon0", 497.6, 0);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::Antiproton) :
      check = FindParticle("Antiproton");
      if(check == 10) {
        fParticleType[N] = new ParticleType ("Antiproton", 938.3, -1);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    default:
      std::cout << "!! -- Particle not in the list, add it using the standard AddParticle -- !!" << '\n';
  }
}

void Particle::AddParticle(PL particle) {
  int const N = fNParticleType;
  ParticleFeatures(particle, N);
}
