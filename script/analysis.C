
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

	TCanvas* can = new TCanvas("can", "Histograms");
	can->Divide(2,2);

	can->cd(1);
	type->SetLineWidth(3);
	type->SetFillColorAlpha(kBlue, .5);
	type->Draw();
	type->GetXaxis()->SetTitle("Particle Type");
	type->GetYaxis()->SetTitle("Number of Particles");

	// CCheck of the shape of the momentum ///////
	can->cd(2);
	TH1F* Mom = (TH1F*)c->Get("momentum");
	Mom->Fit("expo","","");
	Mom->SetFillColorAlpha(kBlue, 0.3);
	Mom->SetLineWidth(6);
	Mom->GetXaxis()->SetTitle("Momentum");
	Mom->GetYaxis()->SetTitle("Occurrencies");
	Mom->Draw();
	gPad->Update();
	TPaveStats* ft = (TPaveStats*)Mom->FindObject("stats");
	ft->SetOptFit(optarg);
	cout<<"----------------------------------\n";
	cout<<Mom->GetMean()<<" - "<<Mom->GetRMS()<<" - "<<Mom->GetMeanError()<<" - "<< 1<<'\n';
	cout<<"----------------------------------\n";

	// Cheack of the angles ////////////////////
	can->cd(3);
	TH1F* Pol = (TH1F*)c->Get("polar");
	Pol->Fit("pol0");
	TF1* f1 = Pol->GetFunction("pol0");
	f1->SetLineColor(kBlack);
	Pol->SetLineColor(kRed);
	Pol->GetXaxis()->SetTitle("Radiants");
	Pol->GetYaxis()->SetTitle("Occurrences");
	Pol->Draw();
	gPad->Update();
	TPaveStats* ft1 = (TPaveStats*)Pol->GetListOfFunctions()->FindObject("stats");
	ft1->SetOptFit(optarg);
	gStyle->SetStatW(.2);
	gStyle->SetStatH(.4);

	can->cd(4);
	TH1F* azim = (TH1F*)c->Get("azim");
	azim->Fit("pol0");
	TF1* f2 = azim->GetFunction("pol0");
	f2->SetLineColor(kBlack);
	azim->SetLineColor(kBlue);
	azim->GetXaxis()->SetTitle("Radiants");
	azim->GetYaxis()->SetTitle("Occurrences");
	azim->Draw();
	gPad->Update();
	TPaveStats* ft5 = (TPaveStats*)azim->FindObject("stats");
	ft5->SetOptFit(optarg);
	can->Print("../fit/anglesfit.pdf");

	// Check the entrance for each histogram

	TH1F* tmom = (TH1F*)c->Get("tmomentum");
	TH1F* imass = (TH1F*)c->Get("invmass");
	TH1F* en = (TH1F*)c->Get("energy");
	TH1F* imd = (TH1F*)c->Get("invmassdis");
	TH1F* imc = (TH1F*)c->Get("invmasscon");
	TH1F* inv1 = (TH1F*)c->Get("invppkmpmkp");
	TH1F* inv2 = (TH1F*)c->Get("invppkppmkm");
	TH1F* dec = (TH1F*)c->Get("decay");

	cout<<"---------------------------------------\n";
	cout<<"Entries Momentum: "<< Mom->GetEntries()<<" - "<< 1E7<<'\n';

	cout<<"---------------------------------------\n";
	cout<<"Entries tMoment: "<< tmom->GetEntries()<<" - "<<1E7<<'\n';

	cout<<"---------------------------------------\n";
	cout<<"Entries invariant mass: "<< imass->GetEntries()<<" - "<<1E5*101*100/2<<'\n';

	cout<<"---------------------------------------\n";
	cout<<"Entries energy: "<< en->GetEntries()<<"- "<<1E7<<'\n';

	cout<<"---------------------------------------\n";
	cout<<"Entries invariant mass opposite: "<< imd->GetEntries()<<" - "<<1E5*101*100*0.495/2<<'\n';

	cout<<"---------------------------------------\n";
	cout<<"Entries invariant mass concord: "<< imc->GetEntries()<<" - "<<1E5*101*100*0.495/2<<'\n';

	cout<<"---------------------------------------\n";
	cout<<"Entries invariant mass 1: "<< inv1->GetEntries()<<" - "<<1E5*101*100<<'\n';

	cout<<"---------------------------------------\n";
	cout<<"Entries invariant mass 2: "<< inv2->GetEntries()<<" - "<<1E5*101*100<<'\n';

	cout<<"---------------------------------------\n";
	cout<<"Entries decay: "<< dec->GetEntries()<<" - "<<1E7*0.01<<'\n';

	cout<<"---------------------------------------\n";
	cout<<"Entries azimutal angles: "<< azim->GetEntries()<<" - "<<1E7<<'\n';

	cout<<"---------------------------------------\n";
	cout<<"Entries polar angles: "<< Pol->GetEntries()<<" - " << 1E7<<'\n';
	cout<<"---------------------------------------\n";


}

// Function that analyze the function for the detection of the Resonance Kaon //////////

void analysis() {
	int optarg = 1111;

	TFile* f = new TFile("Alice_Simulation.root","read");

	TCanvas* can = new TCanvas("cam", "Fits");
	can->Divide(2,2);
	can->cd(1);
	TH1F* Im1 = (TH1F*)f->Get("invmassdis");
	TH1F* Im2 = (TH1F*)f->Get("invmasscon");
	TH1F* diff1 = new TH1F("diff1","Difference 1", 1000, 0, 5);
	diff1->Add(Im1,Im2, -1, 1);
	diff1->Fit("gaus","","",0.5, 1.5);
	diff1->SetAxisRange(0.5, 1.5);
	diff1->GetXaxis()->SetTitle("Invariant Mass (Kg)");
	diff1->GetYaxis()->SetTitle("Occurrences");
	diff1->Draw();
	gPad->Update();
	TPaveStats* ft2 = (TPaveStats*)diff1->FindObject("stats");
	ft2->SetOptFit(optarg);
	ft2->SetOptStat(10);

	can->cd(2);
	TH1F* Im3 = (TH1F*)f->Get("invppkmpmkp");
	TH1F* Im4 = (TH1F*)f->Get("invppkppmkm");
	TH1F* diff2 = new TH1F("diff2","Difference 2", 1000, 0, 5);
	diff2->Add(Im3,Im4, 1, -1);
	diff2->Fit("gaus","","",0.7, 1.5);
	diff2->SetAxisRange(0.7, 1.5);
	diff2->GetXaxis()->SetTitle("Invariant Mass (Kg)");
	diff2->GetYaxis()->SetTitle("Occurrences");
	diff2->Draw();
	gPad->Update();
	TPaveStats* ft3 = (TPaveStats*)diff2->FindObject("stats");
	ft3->SetOptFit(optarg);
	ft3->SetOptStat(10);

	can->cd(3);
	TH1F* kaon = (TH1F*)f->Get("decay");
	kaon->Fit("gaus","","",0.5, 1.25);
	kaon->SetAxisRange(0.5, 1.5);
	kaon->GetXaxis()->SetTitle("Invariant Mass (Kg)");
	kaon->GetYaxis()->SetTitle("Occurrences");
	kaon->Draw();
	gPad->Update();
	TPaveStats* ft4 = (TPaveStats*)kaon->FindObject("stats");
	ft4->SetOptFit(optarg);
	can->Print("../fit/decay_fit.pdf");
	ft4->SetOptStat(2211);
}
