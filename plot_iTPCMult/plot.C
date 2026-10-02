



void plot(){

	TFile *fin=TFile::Open("MultiDistribution.root","READ");


	TH2D *h2D_iTPCPrimaryMult_Trigger_sum = (TH2D*)fin->Get("h2D_iTPCPrimaryMult_Trigger_sum");

	std::vector<TH1D *>h1D_iTPCPrimaryMult;
	for(int i =0 ;i < 5 ;i ++){
		h1D_iTPCPrimaryMult.push_back( (TH1D*)h2D_iTPCPrimaryMult_Trigger_sum->ProjectionX(Form("h1D_iTPCPrimaryMult_%d",i),i+1, i+1) );
		h1D_iTPCPrimaryMult[i]->Scale(1./h1D_iTPCPrimaryMult[i]->Integral(),"width");
	}	


	int color[5]={kBlack,kRed,kBlue,kGreen,kViolet};
	std::vector<std::string> TriggerID={"MB 910001","MB 910003","MB 91013","HM 910802","HM 910804"};
	TCanvas *c1 = new TCanvas("c1","c1",800,600);
	for(int i =0 ;i <5 ;i++){
		h1D_iTPCPrimaryMult[i]->GetXaxis()->SetTitle("Number of iTPC primary tracks");
		h1D_iTPCPrimaryMult[i]->SetLineColor(color[i]);
		h1D_iTPCPrimaryMult[i]->SetMarkerColor(color[i]);
		h1D_iTPCPrimaryMult[i]->SetMarkerStyle(20);
		h1D_iTPCPrimaryMult[i]->SetMarkerSize(1.0);
		h1D_iTPCPrimaryMult[i]->Draw("same");
	}
	TLegend *leg = new TLegend(0.5, 0.6, 0.8, 0.88);
	leg->SetBorderSize(0);
	for(int i =0 ;i < 5;i++){
		leg->AddEntry(h1D_iTPCPrimaryMult[i], TriggerID[i].c_str());
	}
	
	leg->Draw("same");




}