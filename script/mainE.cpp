
#include "library.hpp"
#include <iostream>
#include <cmath>

int main() {
  double const pi = 3.1415926535;

  gRandom->SetSeed(0);

  // std::default_random_engine gen(0);
  // std::uniform_real_distribution<double> dis1(0.0,1.0);
  // std::uniform_real_distribution<double> dis100(0.0,100.0);
  // std::exponential_distribution<double> exp(1);

  Particle::AddParticle(PL::PionPlus);
  Particle::AddParticle(PL::PionMinus);
  Particle::AddParticle(PL::KaonPlus);
  Particle::AddParticle(PL::KaonMinus);
  Particle::AddParticle(PL::Proton);
  Particle::AddParticle(PL::Antiproton);
  Particle::AddParticle("Kaon0",0.89166, 0, 0.05);

  TH1F* type = new TH1F("type", "Particles Type", 7, 0, 7);
  TH1F* momentum = new TH1F("momentum", "Momentum", 10000, 0,10);
  TH1F* tmomentum = new TH1F("tmomentum", "Transversal Momentum", 10000, 0, 10);
  TH1F* invmass = new TH1F("invmass", "Invarian Mass", 10000, 0, 10);
  TH1F* azim = new TH1F("azim", "Azimutal Angol", 10000, 0, pi);
  TH1F* polar = new TH1F("polar", "Polar Angol", 10000, 0, 2*pi);
  TH1F* invmassdis = new TH1F("invmassids", "Invariant Mass opposite charges", 10000, 0, 10);
  TH1F* invmasscon = new TH1F("invmasscon", "invariant Mass same charges", 10000, 0, 10);
  TH1F* invppkmpmkp = new TH1F("invppkmpmkp", "Invariant Mass pion+/kaon- & pion-/kaon+", 10000, 0, 10);
  TH1F* invppkppmkm = new TH1F("invppkppmkm", "Invariant Mass pion+/kaon+ & pion-/kaon-", 10000, 0, 10);
  TH1F* decay = new TH1F("decay", "Invairant mass of particles from the decay", 10000, 0, 10);

  //std::cout << "The following Particles had been updated: " << '\n';
  //Particle::PrintTable();

  int const N = 100;
  int const extra = 20;
  Particle Particella[N+extra];

  for(int i = 0; i < 1E5; ++i) {
    int ExtraCounter = 0;
    for(int j = 0; j < (N+ExtraCounter); ++j) {

      double phi = 2*pi*gRandom->Uniform(0.0,1.0);
      double theta = pi*gRandom->Uniform(0.0,1.0);

      azim->Fill(theta);
      polar->Fill(phi);

      double P = gRandom->Exp(1.0);

      double Px = P*cos(phi)*cos(theta);
      double Py = P*cos(phi)*sin(theta);
      double Pz = P*sin(phi);

      Particella[j].SetMomentum(Px, Py, Pz);

      //Setting the type ///////////////////////////
      double prob = gRandom->Uniform(0.0,100.0);

      if(prob<40) {
        Particella[j].SetIndex("Pion+");
      } else if (prob<80) {
        Particella[j].SetIndex("Pion-");
      } else if (prob<85) {
        Particella[j].SetIndex("Kaon+");
      } else if (prob<90) {
        Particella[j].SetIndex("Kaon-");
      } else if (prob<94.5) {
        Particella[j].SetIndex("Proton");
      } else if (prob<99) {
        Particella[j].SetIndex("Antiproton");
      } else {
        Particella[j].SetIndex("Kaon0");

        ++ExtraCounter;
        int c = ExtraCounter + N;

        double chance = gRandom->Uniform(0.0,1.0);
        if(chance < 0.5) {
          Particella[c].SetIndex("Pion+");
          Particella[c+1].SetIndex("Kaon-");
        } else {
          Particella[c].SetIndex("Pion-");
          Particella[c+1].SetIndex("Kaon+");
        }
        int check = Particella[j].Decay2Body(Particella[c], Particella[c+1]);
        if (check != 0) { return check; }
      }

      int index = Particella[j].GetIndex();
      type->Fill(index);
      double PModule = sqrt(Particella[j].GetMomentum());
      momentum->Fill(PModule);
      double PTModule = sqrt(Particella[j].GetTrasMomentum());
      tmomentum->Fill(PTModule);
    }
    double MassInv;
    for(int k = 0; k <N; ++k) {
      for(int h = 0; h<N; ++h){
        MassInv = Particella[k].GetInvMass(Particella[h]);
        invmass->Fill(MassInv);
        if(Particella[k].GetCharge() != Particella[h].GetCharge()) {
          double MassInvCondition = Particella[k].GetInvMass(Particella[h]);
          invmassdis->Fill(MassInvCondition);
        } else if(Particella[k].GetCharge() == Particella[h].GetCharge()) {
          double MassInvCondition = Particella[k].GetInvMass(Particella[h]);
          invmasscon->Fill(MassInvCondition);
        }
        if (Particella[k].GetName() == "Pion+" && Particella[h].GetName() == "Kaon-") {
          double MassInvCondition = Particella[k].GetInvMass(Particella[h]);
          invppkmpmkp->Fill(MassInvCondition);
        } else if(Particella[k].GetName() == "Pion-" && Particella[h].GetName() == "Kaon+") {
          double MassInvCondition = Particella[k].GetInvMass(Particella[h]);
          invppkmpmkp->Fill(MassInvCondition);
        } else if (Particella[k].GetName() == "Pion+" && Particella[h].GetName() == "Kaon+") {
          double MassInvCondition = Particella[k].GetInvMass(Particella[h]);
          invppkppmkm->Fill(MassInvCondition);
        } else if(Particella[k].GetName() == "Pion-" && Particella[h].GetName() == "Kaon-") {
          double MassInvCondition = Particella[k].GetInvMass(Particella[h]);
          invppkppmkm->Fill(MassInvCondition);
        }
      }
      for(int k = N; k <= N+ExtraCounter; ++k) {
        for (int h = N; h <= N+ExtraCounter; ++h) {
          if(k!=h) {
            double MassInvCondition = Particella[k].GetInvMass(Particella[h]);
            decay->Fill(MassInvCondition);
          }
        }
      }
    }
  }

  TCanvas *canv1 = new TCanvas("canv1", "Type");
  type->Draw();
  TCanvas *canv2 = new TCanvas("canv2", "Momentum");
  momentum->Draw();
  TCanvas *canv3 = new TCanvas("canv3", "tMomentum");
  tmomentum->Draw();
  TCanvas *canv4 = new TCanvas("canv4", "invMass");
  invmass->Draw();
  TCanvas *canv5 = new TCanvas("canv5", "polarAngle");
  polar->Draw();
  TCanvas *canv6 = new TCanvas("canv6", "azimutalAngle");
  azim->Draw();
  TCanvas *canv7 = new TCanvas("canv7", "Invariant Mass opposite charges");
  invmassdis->Draw();
  TCanvas *canv8 = new TCanvas("canv8", "invariant Mass same charges");
  invmasscon->Draw();
  TCanvas *canv9 = new TCanvas("canv9", "Invariant Mass pion+/kaon- & pion-/kaon+");
  invppkmpmkp->Draw();
  TCanvas *canv10 = new TCanvas("canv10", "Invariant Mass pion+/kaon+ & pion-/kaon-");
  invppkppmkm->Draw();
  TCanvas *canv11 = new TCanvas("canv11", "Decay");
  decay->Draw();

  canv1->Print("../histograms/type.pdf");
  canv2->Print("../histograms/Momentum.pdf");
  canv3->Print("../histograms/tMomentum.pdf");
  canv4->Print("../histograms/invMass.pdf");
  canv5->Print("../histograms/polarAngle.pdf");
  canv6->Print("../histograms/azimutalAngle.pdf");
  canv7->Print("../histograms/invmassdis.pdf");
  canv8->Print("../histograms/invmasscon.pdf");
  canv9->Print("../histograms/invppkmpmkp.pdf");
  canv10->Print("../histograms/invppkppmkm.pdf");
  canv11->Print("../histograms/decay.pdf");

  TFile* RFile = new TFile("ALICE_Simulation.root", "RECREATE");
  RFile->cd();
  type->Write();
  momentum->Write();
  tmomentum->Write();
  invmass->Write();
  polar->Write();
  azim->Write();
  invmassdis->Write();
  invmasscon->Write();
  invppkmpmkp->Write();
  invppkppmkm->Write();
  decay->Write();
  RFile->Close();
  RFile->ls();

  return 0;
}
