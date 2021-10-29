
#include "../librarys/library.hpp"
#include <iostream>
#include <cmath>

void ProgressionBar(int Progression) {
  double n = (Progression/5.22E8);
  std::cout << "[";
    int pos = 70 * n;
    for (int i = 0; i < 70; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(n * 100.0) << " %\r";
    std::cout.flush();
}

int main() {
  double const pi = 3.1415926535;
  int progression = 0;
  TRandom* Random = new TRandom();
  Random->SetSeed(0);

  Particle::AddParticle(PL::PionPlus);
  Particle::AddParticle(PL::PionMinus);
  Particle::AddParticle(PL::KaonPlus);
  Particle::AddParticle(PL::KaonMinus);
  Particle::AddParticle(PL::Proton);
  Particle::AddParticle(PL::Antiproton);
  Particle::AddParticle(PL::Kaon0);

  TH1F* type = new TH1F("type", "Particles Type", 7, 0, 7);
  type->GetXaxis()->TAxis::SetBinLabel(1, "Pion+");
  type->GetXaxis()->TAxis::SetBinLabel(2, "Pion-");
  type->GetXaxis()->TAxis::SetBinLabel(3, "Kaon+");
  type->GetXaxis()->TAxis::SetBinLabel(4, "kaon-");
  type->GetXaxis()->TAxis::SetBinLabel(5, "Proton");
  type->GetXaxis()->TAxis::SetBinLabel(6, "Antiproton");
  type->GetXaxis()->TAxis::SetBinLabel(7, "Kaon0");

  TH1F* momentum = new TH1F("momentum", "Momentum", 1000, 0, 7);
  TH1F* tmomentum = new TH1F("tmomentum", "Transversal Momentum", 1000, 0, 7);
  TH1F* invmass = new TH1F("invmass", "Invarian Mass", 1000, 0, 5);
  TH1F* energy = new TH1F("energy","Energy", 1000, 0, 7);
  TH1F* azim = new TH1F("azim", "Azimutal Angol", 1000, 0, pi);
  TH1F* polar = new TH1F("polar", "Polar Angol", 1000, 0, 2*pi);
  TH1F* invmassdis = new TH1F("invmassdis", "Invariant Mass opposite charges", 1000, 0, 5);
  TH1F* invmasscon = new TH1F("invmasscon", "Invariant Mass same charges", 1000, 0, 5);
  TH1F* invppkmpmkp = new TH1F("invppkmpmkp", "Invariant Mass pion+/kaon- & pion-/kaon+", 1000, 0, 5);
  invppkmpmkp->SetLineColor(kRed);
  TH1F* invppkppmkm = new TH1F("invppkppmkm", "Invariant Mass pion+/kaon+ & pion-/kaon-", 1000, 0, 5);
  invppkppmkm->SetLineColor(kBlue);
  TH1F* decay = new TH1F("decay", "Invairant mass of particles from the decay", 1000, 0, 5);

  invmass->Sumw2();
  invmassdis->Sumw2();
  invmasscon->Sumw2();
  invppkmpmkp->Sumw2();
  invppkppmkm->Sumw2();
  decay->Sumw2();

  int const N = 100;
  int const extra = 20;
  Particle Particella[N+extra];

  for(int i = 0; i < 1E5; ++i) {
    int ExtraCounter = 0;
    for(int j = 0; j < (N); ++j) {

      double phi = 2*pi*Random->Uniform(0.0,1.0);
      double theta = pi*Random->Uniform(0.0,1.0);

      azim->Fill(theta);
      polar->Fill(phi);

      double P = Random->Exp(1.0);

      double Px = P*cos(phi)*cos(theta);
      double Py = P*cos(phi)*sin(theta);
      double Pz = P*sin(phi);

      Particella[j].SetMomentum(Px, Py, Pz);

      //Setting the type ///////////////////////////
      double prob = Random->Uniform(0.0,100.0);

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
        int c = ExtraCounter + N;
        double chance = Random->Uniform(0.0,1.0);
        if(chance < 0.5) {
          Particella[c].SetIndex("Pion+");
          Particella[c+1].SetIndex("Kaon-");
        } else {
          Particella[c].SetIndex("Pion-");
          Particella[c+1].SetIndex("Kaon+");
        }
        int check = Particella[j].Decay2body(Particella[c], Particella[c+1]);
        if (check != 0) return check;
        double MassInvCondition = Particella[c].GetInvMass(Particella[c+1]);
        decay->Fill(MassInvCondition);
        ExtraCounter = ExtraCounter +2;
      }
      int index = Particella[j].GetIndex();
      type->Fill(index);
      double PTModule = sqrt(Particella[j].GetTrasMomentum());
      tmomentum->Fill(PTModule);
      double PModule = sqrt(Particella[j].GetMomentum());
      momentum->Fill(PModule);
      if(Particella[j].GetName() != "Kaon0") {
        double Energy = Particella[j].GetTotalEnergy();
        energy->Fill(Energy);
      }
      ++progression;
    }
    double MassInv;
   for(int k = 0; k <N+ExtraCounter; ++k) {
     for(int h = k+1 ; h<N+ExtraCounter; ++h){
       MassInv = Particella[k].GetInvMass(Particella[h]);
       invmass->Fill(MassInv);
       if((Particella[k].GetCharge() * Particella[h].GetCharge()) < 0) {
         double MassInvCondition = Particella[k].GetInvMass(Particella[h]);
         invmassdis->Fill(MassInvCondition);
       } else if((Particella[k].GetCharge() * Particella[h].GetCharge()) > 0) {
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
       ++progression;
     }
   }
    ProgressionBar(progression);
  }

  TCanvas *canv1 = new TCanvas("canv1", "Type");
  type->Draw();
  TCanvas *canv2 = new TCanvas("canv2", "Momentum");
  canv2->Divide(1,2);
  canv2->cd(1);
  momentum->Draw();
  canv2->cd(2);
  tmomentum->Draw();
  TCanvas *canv12 = new TCanvas("canv12", "energy");
  energy->Draw();
  TCanvas *canv4 = new TCanvas("canv4", "invMass");
  invmass->Draw();
  TCanvas *canv5 = new TCanvas("canv5", "polarAngle");
  polar->Draw();
  TCanvas *canv6 = new TCanvas("canv6", "azimutalAngle");
  azim->Draw();
  TCanvas *canv7 = new TCanvas("canv7", "Invariant Mass opposite charges");
  invmassdis->Draw("histo");
  TCanvas *canv8 = new TCanvas("canv8", "invariant Mass same charges");
  invmasscon->Draw("histo");
  TCanvas *canv9 = new TCanvas("canv9", "Invariant Mass of pion and kaon");
  canv9->Divide(1,2);
  canv9->cd(1);
  invppkppmkm->Draw("histo");
  canv9->cd(2);
  invppkmpmkp->Draw("histo");
  TCanvas *canv10 = new TCanvas("canv10", "Invariant Mass pion+/kaon+ & pion-/kaon-");
  invppkppmkm->Draw("histo");
  invppkmpmkp->Draw("histo same");
  TCanvas *canv11 = new TCanvas("canv11", "Decay");
  decay->Draw("histo");

  canv1->Print("../histograms/type.pdf");
  canv2->Print("../histograms/Momentums.pdf");
  canv12->Print("../histograms/energy.pdf");
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
  energy->Write();
  invmass->Write();
  polar->Write();
  azim->Write();
  invmassdis->Write();
  invmasscon->Write();
  invppkmpmkp->Write();
  invppkppmkm->Write();
  decay->Write();
  RFile->ls();
  RFile->Close();


  return 0;
}
