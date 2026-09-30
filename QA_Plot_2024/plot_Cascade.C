

void plot_Cascade(){
	TFile *fin=TFile::Open("testR3L_DeltaR0p5.root");
	TH1D *h1D_TestResonanceMass = (TH1D*)fin->Get("h1D_TestResonanceMass");
	h1D_TestResonanceMass->GetXaxis()->SetTitle("Invariant Mass (p_{1}+#pi_{1}+#pi_{3}) (GeV/c^{2})");
	h1D_TestResonanceMass->GetXaxis()->CenterTitle();
	h1D_TestResonanceMass->GetYaxis()->SetTitle("Counts");
	h1D_TestResonanceMass->GetYaxis()->SetTitleOffset(1.35);
	h1D_TestResonanceMass->GetYaxis()->CenterTitle();
	h1D_TestResonanceMass->SetMarkerStyle(20);
	h1D_TestResonanceMass->SetMarkerSize(0.3);
	h1D_TestResonanceMass->SetTitle("");
	h1D_TestResonanceMass->GetXaxis()->SetRangeUser(1.2,1.5);
	TCanvas *c1= new TCanvas("c1","c1",800,600);
	c1->SetFrameLineWidth(3);
	h1D_TestResonanceMass->Draw();








}