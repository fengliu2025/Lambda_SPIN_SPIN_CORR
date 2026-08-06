


void plot_EventStat(){

	TFile *fin = TFile::Open("EventStat.root");

	TH1F *hEventStat1_sum = (TH1F*)fin->Get("hEventStat1_sum");
	hEventStat1_sum->GetYaxis()->SetTitleSize(0.05);
	hEventStat1_sum->GetXaxis()->SetTitleSize(0.0);
	hEventStat1_sum->GetXaxis()->SetLabelSize(0.07);
	hEventStat1_sum->SetTitle("");
	hEventStat1_sum->GetYaxis()->SetRangeUser(0,3300000000);
	gStyle->SetOptStat(0);
	TCanvas *c = new TCanvas("c","c",800,600);
	hEventStat1_sum->Draw();
	c->SaveAs("EventStat.pdf");
}