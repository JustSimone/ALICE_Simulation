void macro(){
	TFile* f = new TFile("Alice_Simulation.root", "read");
	TH1F* H1 =(TH1F*)f->Get("invmassdis");
	TH1F* H2 =(TH1F*)f->Get("invmasscon");
	H1->SetLineColorAlpha(kBlue,1.);
	H1->SetLineWidth(2);
	H2->SetLineColorAlpha(kRed,1.);
	H2->SetLineWidth(2);

	TCanvas* c = new TCanvas();
	H1->Draw("histo");
	H2->Draw("histo same");
}
