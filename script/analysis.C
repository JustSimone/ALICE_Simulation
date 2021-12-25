
void setStyle() {
	gROOT->SetStyle("Modern");
	gStyle->SetPalette(56);
	gStyle->SetOptFit(111);
}

// Function that checks the generation of the values ////////

void Checks() {

	int optarg = 1111;

	// Check of the generqation of particles /////////
	double particleProb[7];

 	particleProb[0]= 0.4;
 	particleProb[1]= 0.4;
 	particleProb[2]= 0.05;
 	particleProb[3]= 0.05;
 	particleProb[4]= 0.045;
 	particleProb[5]= 0.045;
 	particleProb[6]= 0.01;

	TFile* c = new TFile("Alice_Simulation.root","read");
	TH1F* type = (TH1F*)c->Get("type");
	cout<<"Bin Content - Error - Theo. Val.\n";
	cout<<"----------------------------------\n";
	for(int i=1; i<8; ++i) {
		cout<<type->GetBinContent(i)<<" - "<<type->GetBinError(i)<< " - "<< particleProb[i-1]*1E7<< '\n';
		cout<<"----------------------------------\n";
	}

	// CCheck of the shape of the momentum ///////
	TCanvas* c1 = new TCanvas("c1", "Momento");
	TH1F* Mom = (TH1F*)c->Get("momentum");
	Mom->Fit("expo","","");
	Mom->SetFillColorAlpha(kBlue, 0.3);
	Mom->SetLineWidth(6);
	Mom->Draw();
	c1->Print("--/fit//Momwntumfit.png");
	c1->Print("../fit/Momentumfit.pdf");
	gPad->Update();
	TPaveStats* ft = (TPaveStats*)Mom->FindObject("stats");
	ft->SetOptFit(optarg);
	cout<<"----------------------------------\n";
	cout<<Mom->GetMean()<<" - "<<Mom->GetRMS()<<" - "<< 1<<'\n';
	cout<<"----------------------------------\n";

	// Cheack of the angles ////////////////////
	TCanvas* c2 = new TCanvas("c2", "Angoli");
	c2->Divide(1,2);

	c2->cd(1);
	TH1F* Pol = (TH1F*)c->Get("polar");
	Pol->Fit("pol0");
	TF1* f1 = Pol->GetFunction("pol0");
	f1->SetLineColor(kBlack);
	Pol->SetLineColor(kRed);
	Pol->Draw();
	gPad->Update();
	TPaveStats* ft1 = (TPaveStats*)Pol->GetListOfFunctions()->FindObject("stats");
	ft1->SetOptFit(optarg);
	gStyle->SetStatW(.2);
	gStyle->SetStatH(.4);

	c2->cd(2);
	TH1F* azim = (TH1F*)c->Get("azim");
	azim->Fit("pol0");
	TF1* f2 = azim->GetFunction("pol0");
	f2->SetLineColor(kBlack);
	azim->SetLineColor(kBlue);
	azim->Draw();
	gPad->Update();
	TPaveStats* ft5 = (TPaveStats*)azim->FindObject("stats");
	ft5->SetOptFit(optarg);
	c2->Print("../fit/anglesfit.png");
	c2->Print("../fit/anglesfit.pdf");
}

// Function that analyze the function for the detection of the Resonance Kaon //////////

void analysis() {
	int optarg = 1111;
	TColor* myYellow = gROOT->GetColor(10);
	TFile* f = new TFile("Alice_Simulation.root","read");

	TCanvas* c3 = new TCanvas("c3", "Cariche");
	TH1F* Im1 = (TH1F*)f->Get("invmassdis");
	TH1F* Im2 = (TH1F*)f->Get("invmasscon");
	TH1F* diff1 = new TH1F("diff1","Difference 1", 1000, 0, 5);
	diff1->Add(Im1,Im2, -1, 1);
	diff1->Fit("gaus","","",0.5, 1.5);
	diff1->SetAxisRange(0.5, 1.5);
	diff1->Draw();
	gPad->Update();
	TPaveStats* ft2 = (TPaveStats*)diff1->FindObject("stats");
	c3->Print("../fit/Cariche_fit.pdf");
	ft2->SetOptFit(optarg);
	ft2->SetOptStat(10);

	TCanvas* c4 = new TCanvas("c4", "Pioni e Kaoni");
	TH1F* Im3 = (TH1F*)f->Get("invppkmpmkp");
	TH1F* Im4 = (TH1F*)f->Get("invppkppmkm");
	TH1F* diff2 = new TH1F("diff2","Difference 2", 1000, 0, 5);
	diff2->Add(Im3,Im4, 1, -1);
	diff2->Fit("gaus","","",0.7, 1.5);
	diff2->SetAxisRange(0.7, 1.5);
	diff2->Draw();
	gPad->Update();
	TPaveStats* ft3 = (TPaveStats*)diff2->FindObject("stats");
	c4->Print("../fit/pion_kaon_fit.pdf");
	ft3->SetOptFit(optarg);
	ft3->SetOptStat(10);

	TCanvas* c5 = new TCanvas("c5", "Decadimento Kaoni");
	TH1F* kaon = (TH1F*)f->Get("decay");
	kaon->Fit("gaus","","",0.5, 1.25);
	kaon->SetAxisRange(0.5, 1.5);
	kaon->Draw();
	gPad->Update();
	TPaveStats* ft4 = (TPaveStats*)kaon->FindObject("stats");
	ft4->SetOptFit(optarg);
	c5->Print("../fit/decay_fit.pdf");
	ft4->SetOptStat(2211);
}
