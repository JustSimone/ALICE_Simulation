#include "../../libraries/library.hpp"

#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <random>

int Particle::fNParticleType = 0;
ParticleType* Particle::fParticleType[fMaxNumParticleType];

// Public Methods //////////////////////////////////////
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

int Particle::Decay2body(Particle &dau1,Particle &dau2) const {
  if(GetMass() == 0.0){
    printf("Decayment cannot be preformed if mass is zero\n");
    return 1;
  }

  double massMot = GetMass();
  double massDau1 = dau1.GetMass();
  double massDau2 = dau2.GetMass();

  if(fIndex < 10){ // add width effect

    // gaussian random numbers

    float x1, x2, w, y1, y2;

    double invnum = 1./RAND_MAX;
    do {
      x1 = 2.0 * rand()*invnum - 1.0;
      x2 = 2.0 * rand()*invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while ( w >= 1.0 );

    w = sqrt( (-2.0 * log( w ) ) / w );
    y1 = x1 * w;
    y2 = x2 * w;
    massMot += fParticleType[fIndex]->GetParticleWidth() * y1;
  }
  if(massMot < massDau1 + massDau2){
    printf("Decayment cannot be preformed because mass is too low in this channel\n");
    return 2;
  }
  double pout = sqrt((massMot*massMot - (massDau1+massDau2)*(massDau1+massDau2))*(massMot*massMot - (massDau1-massDau2)*(massDau1-massDau2)))/massMot*0.5;
  double norm = 2*M_PI/RAND_MAX;
  double phi = rand()*norm;
  double theta = rand()*norm*0.5 - M_PI/2.;
  dau1.SetMomentum(pout*sin(theta)*cos(phi),pout*sin(theta)*sin(phi),pout*cos(theta));
  dau2.SetMomentum(-pout*sin(theta)*cos(phi),-pout*sin(theta)*sin(phi),-pout*cos(theta));
  double energy = sqrt(fPx*fPx + fPy*fPy + fPz*fPz + massMot*massMot);
  double bx = fPx/energy;
  double by = fPy/energy;
  double bz = fPz/energy;
  dau1.Boost(bx,by,bz);
  dau2.Boost(bx,by,bz);
  return 0;
}

void Particle::Boost(double bx, double by, double bz)
{
  double energy = GetTotalEnergy();
  //Boost this Lorentz vector
  double b2 = bx*bx + by*by + bz*bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx*fPx + by*fPy + bz*fPz;
  double gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;

  fPx += gamma2*bp*bx + gamma*bx*energy;
  fPy += gamma2*bp*by + gamma*by*energy;
  fPz += gamma2*bp*bz + gamma*bz*energy;
}

// Constructor //////////////////////////////////////
Particle::Particle(std::string name, double Px = 0, double Py = 0, double Pz = 0):
fPx(Px),
fPy(Py),
fPz(Pz),
fIndex (FindParticle(name))
{ if(fIndex == 10) { std::cout << "!! -- This Type of Particle does not Excist -- !!" << '\n'; } }

// Getter Methods //////////////////////////////////////
int Particle::GetIndex() const { return fIndex; }

int Particle::GetCharge() const {return fParticleType[fIndex]->GetParticleCharge(); }

std::string Particle::GetName() const {return fParticleType[fIndex]->GetParticleName();}

double Particle::GetPx() const { return fPx; }

double Particle::GetPy() const { return fPy; }

double Particle::GetPz() const { return fPz; }

double Particle::GetMass() const {
  return (fParticleType[fIndex]->GetParticleMass());
}

double Particle::GetMomentum() const {
  return (fPx*fPx + fPy*fPy + fPz*fPz);
}

double Particle::GetTrasMomentum() const {
  return fPx*fPx + fPy*fPy;
}

double Particle::GetTotalEnergy() const {
  double m = GetMass();
  double p2 = GetMomentum();
  return sqrt(m*m + p2);
}

double Particle::GetInvMass(Particle& p) const {
  double E1 = GetTotalEnergy();
  double E2 = p.GetTotalEnergy();
  double Psum = (fPx+p.GetPx())*(fPx+p.GetPx())+(fPy+p.GetPy())*(fPy+p.GetPy())+(fPz+p.GetPz())*(fPz+p.GetPz());
  double M = sqrt((E1+ E2)*(E1+ E2) - Psum);
  return M;
}

// Setter Methods //////////////////////////////////////
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

// Printer //////////////////////////////////////
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

// Particles List //////////////////////////////////////
void Particle::ParticleFeatures(PL& particle, int const N) {
  int check;
  switch (particle) {
    case (PL::Electron):
      check = FindParticle("Electron");
      if (check == 10) {
        fParticleType[N] = new ParticleType ("Electron", 0.0005109, -1);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::Proton) :
      check = FindParticle("Proton");
      if(check == 10) {
        fParticleType[N] = new ParticleType ("Proton", 0.938327, +1);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::Positron) :
      check = FindParticle("Positron");
      if(check == 10) {
        fParticleType[N] = new ParticleType ("Positron", 0.0005109, +1);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::PionMinus):
      check = FindParticle("Pion-");
      if(check == 10) {
        fParticleType[N] = new ParticleType ("Pion-", 0.13957, +1);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::PionPlus) :
      check = FindParticle("Pion+");
      if(check == 10) {
        fParticleType[N] = new ParticleType ("Pion+", 0.13957, -1);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::Pion0) :
      check = FindParticle("Pion0");
      if(check == 10) {
        fParticleType[N] = new ParticleType ("Pion0", 0.1350, 0);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::KaonPlus) :
      check = FindParticle("Kaon+");
      if(check == 10) {
        fParticleType[N] = new ParticleType ("Kaon+", 0.49367, +1);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::KaonMinus) :
      check = FindParticle("Kaon-");
      if(check == 10) {
        fParticleType[N] = new ParticleType ("Kaon-", 0.49367, -1);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::Kaon0) :
      check = FindParticle("Kaon0");
      if(check == 10) {
        fParticleType[N] = new ResonanceType ("Kaon0", 0.89166, 0, 0.05);
        ++fNParticleType;
      } else {
        std::cout << "!! -- The particle Does alreay excist -- !!  " << '\n';
      }
    break;
    case (PL::Antiproton) :
      check = FindParticle("Antiproton");
      if(check == 10) {
        fParticleType[N] = new ParticleType ("Antiproton", 0.93827, -1);
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
