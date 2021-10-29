void setStyle() {
	gROOT->SetStyle("Modern");
	gStyle->SetPalette(59);
	gStyle->SetOptFit(221);
}

void macro() {

	setStyle();

	TFile* f = new TFile("Alice_Simulation.root","read");

	TCanvas* c1 = new TCanvas("c1", "Momento");
	TH1F* Mom = (TH1F*)f->Get("momentum");
	Mom->Fit("expo","","");
	Mom->Draw();

	TCanvas* c2 = new TCanvas("c1", "Angoli");
	c2->Divide(2,1);
	c2->cd(1);
	TH1F* Pol = (TH1F*)f->Get("polar");
	Pol->Fit("pol0");
	Pol->Draw();
	c2->cd(2);
	TH1F* azim = (TH1F*)f->Get("azim");
	azim->Fit("pol0");
	azim->Draw();

	TCanvas* c3 = new TCanvas("c3", "Cariche discordi");
	TH1F* Im1 = (TH1F*)f->Get("invmassdis");
	TH1F* Im2 = (TH1F*)f->Get("invmasscon");
	TH1F* diff1 = new TH1F("diff1","diff1", 1000, 0, 5);
	diff1->Add(Im1,Im2, -1, 1);
	diff1->Fit("gaus","","",0.5, 1.5);
	diff1->SetAxisRange(0.5, 1.5);
	diff1->Draw();

	TCanvas* c4 = new TCanvas("c4", "Pioni e Kaoni");
	TH1F* Im3 = (TH1F*)f->Get("invppkmpmkp");
	TH1F* Im4 = (TH1F*)f->Get("invppkppmkm");
	TH1F* diff2 = new TH1F("diff2","diff2", 1000, 0, 5);
	diff2->Add(Im3,Im4, 1, -1);
	diff2->SetAxisRange(0.5, 1.5);
	diff2->Draw();
}
