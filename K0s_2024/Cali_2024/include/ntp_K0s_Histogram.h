#ifndef ntp_K0s_Histogram_h
#define ntp_K0s_Histogram_h

//include the header file here 
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TGraph.h>

#include <string>
#include <iostream>


#include "ntp_K0s_Reader_v2.h"


#include "constants.h"
class ntp_K0s_Histogram {
public : 
	ntp_K0s_Reader *Reader;

	std::string OutPutFile;

	//Histograms for QA plot
	//QA plots. Basics Distribution of daughter particles.(After Selection).

	TH1D *h1D_Vz;
	TH1D *h1D_TrigID;

	TH2D *h2D_pair_Pt;
	TH2D *h2D_pair_Eta;
	TH2D *h2D_pair_Phi;
	TH2D *h2D_pair_Mass;

	TH1D *h1D_pair_Charge;
	TH1D *h1D_pair_DauDCA;
	TH1D *h1D_pair_CosTheta;
	TH1D *h1D_pair_DecayL;
	TH1D *h1D_pair_DCA;


	TH2D *h2D_p1_Pt;
	TH1D *h1D_p1_Eta;
	TH1D *h1D_p1_Phi;
	TH1D *h1D_p1_Dca;
	TH1D *h1D_p1_Dcaxy;
	TH1D *h1D_p1_nSigmaPion;

	TH2D *h2D_p2_Pt;
	TH1D *h1D_p2_Eta;
	TH1D *h1D_p2_Phi;
	TH1D *h1D_p2_Dca;
	TH1D *h1D_p2_Dcaxy;
	TH1D *h1D_p2_nSigmaPion;

	TGraph *gr_ScaleFactor;


	std::vector<TH1D *> h1D_pair_Mass;
	std::vector<TH2D *> h2D_pairPt_pairMass;
	std::vector<TH2D *> h2D_pairEta_pairMass;
	std::vector<TH2D *> h2D_pairPhi_pairMass;
	std::vector<TH2D *> h2D_pairDecayL_pairMass;
	std::vector<TH2D *> h2D_p1Pt_pairMass;
	std::vector<TH2D *> h2D_p2Pt_pairMass;

	double Cali_scale_max;
	double Cali_scale_min;
	int Cali_NPoint  ;



	ntp_K0s_Histogram();
	ntp_K0s_Histogram(ntp_K0s_Reader *reader,std::string outPutFile);
	void InitHitogram();
	void Fill_EventInfo();
	void Fill_K0sInfo(int pair_Charge, float pair_DauDCA, float pair_Theta, float pair_DecayL);
	void Fill_K0sInfo(int i_scale, TLorentzVector K0s_scaled,float pair_DecayL);
	void Fill_DauPionInfo(float p1_Eta,float p1_Phi ,float p1_Dca, float p1_Dcaxy, float p1_nSigmaPion ,float p2_Eta,float p2_Phi ,float p2_Dca, float p2_Dcaxy, float p2_nSigmaPion);
	void Fill_DauPionInfo(int i_scale, TLorentzVector K0s_scaled,TLorentzVector Pion1_scaled,TLorentzVector Pion2_scaled);

	void Reset();

	void WriteAll();

};

ntp_K0s_Histogram::ntp_K0s_Histogram()
{	
	Cali_scale_max = 1.000;
	Cali_scale_min = 0.995;
	Cali_NPoint = 10;
}

ntp_K0s_Histogram::ntp_K0s_Histogram(ntp_K0s_Reader *reader,std::string outPutFile)
:Reader(reader),OutPutFile(outPutFile)
{	
	Cali_scale_max = 1.000;
	Cali_scale_min = 0.995;
	Cali_NPoint = 10;
}

void ntp_K0s_Histogram::InitHitogram(){
	TH1::SetDefaultSumw2(kTRUE);

	h1D_Vz 				 = new TH1D("h1D_Vz","h1D_vz",200,-100,100);	
	h1D_TrigID			 = new TH1D("h1D_TrigID","h1D_TrigID",6,0.5,6.5);

	h2D_pair_Pt    = new TH2D("h2D_pair_Pt","h2D_pair_Pt",Cali_NPoint+1,-0.5,Cali_NPoint+0.5,1000,0,10 );
	h2D_pair_Eta   = new TH2D("h2D_pair_Eta","h2D_pair_Eta",Cali_NPoint+1,-0.5,Cali_NPoint+0.5,1000,-3,3);
	h2D_pair_Phi   = new TH2D("h2D_pair_Phi","h2D_pair_phi",Cali_NPoint+1,-0.5,Cali_NPoint+0.5,1000,-2*3.14, 2*3.14);
	h2D_pair_Mass  = new TH2D("h2D_pair_Mass","h2D_pair_Mass",Cali_NPoint+1,-0.5,Cali_NPoint+0.5,1000,0.45,0.55);

	h1D_pair_Charge= new TH1D("h1D_pair_Charge","h1D_pair_Charge",4,-2,2);
	h1D_pair_DauDCA= new TH1D("h1D_pair_DauDCA","h1D_pair_DauDCA",100,-5,5);
	h1D_pair_CosTheta= new TH1D("h1D_pair_CosTheta","h1D_pair_CosTheta",100,0.99,1.01);
	h1D_pair_DecayL = new TH1D("h1D_piar_DecayL","h1D_pair_DecayL",100,0,30);
	h1D_pair_DCA    = new TH1D("h1D_pair_DCA","h1D_pair_DCA",100,-2,2);

	h2D_p1_Pt = new TH2D("h2D_p1_Pt","h2D_p1_Pt",Cali_NPoint+1,-0.5,Cali_NPoint+0.5,1000,0,10);
	h1D_p1_Eta     = new TH1D("h1D_p1_Eta","h1D_p1_Eta",100,-3,3); 
	h1D_p1_Phi     = new TH1D("h1D_p1_Phi","h1D_p1_Phi",100,-2*TMath::Pi(),2*TMath::Pi() ); 
	h1D_p1_Dca     = new TH1D("h1D_p1_Dca","h1D_p1_Dca",100,-1,1);
	h1D_p1_Dcaxy   = new TH1D("h1D_p1_Dcaxy","h1D_p1_Dcaxy",100,-1,1);
	h1D_p1_nSigmaPion = new TH1D("h1D_p1_nSigmaPion","h1D_p1_nSigmaPion",100,-5,5);

	h2D_p2_Pt = new TH2D("h2D_p2_Pt","h2D_p2_Pt",Cali_NPoint+1,-0.5,Cali_NPoint+0.5,1000,0,10);
	h1D_p2_Eta     = new TH1D("h1D_p2_Eta","h1D_p2_Eta",100,-3,3);
	h1D_p2_Phi     = new TH1D("h1D_p2_Phi","h1D_p2_Phi",100,-2*TMath::Pi(),2*TMath::Pi() ); 
	h1D_p2_Dca     = new TH1D("h1D_p2_Dca","h1D_p2_Dca",100,-1,1);
	h1D_p2_Dcaxy   = new TH1D("h1D_p2_Dcaxy","h1D_p2_Dcaxy",100,-1,1);
	h1D_p2_nSigmaPion = new TH1D("h1D_p2_nSigmaPion","h1D_p2_nSigmaPion",100,-5,5);



	for(int i =0 ; i <Cali_NPoint+1 ;i++){
		h1D_pair_Mass.push_back( 			new TH1D( Form("h1D_pair_Mass_%d",i)        	, Form("h1D_pair_Mass_%d",i)       		, 1000,0.45,0.55                      )       ) ;
		h2D_pairPt_pairMass.push_back(  	new TH2D( Form("h2D_pairPt_pairMass_%d",i)  	, Form("h2D_pairPt_pairMass_%d",i) 		, 100,0,10,1000,0.45,0.55             )       ) ;
		h2D_pairEta_pairMass.push_back(     new TH2D( Form("h2D_pairEta_pairMass_%d",i) 	, Form("h2D_pairEta_pairMass_%d",i)		, 100,-3,3,1000,0.45,0.55             )       ) ;
		h2D_pairPhi_pairMass.push_back(     new TH2D( Form("h2D_pairPhi_pairMass_%d",i) 	, Form("h2D_pairPhi_pairMass_%d",i)		, 100,-2*3.14,2*3.14,1000,0.45,0.55   )       ) ;
		h2D_pairDecayL_pairMass.push_back(  new TH2D( Form("h2D_pairDecayL_pairMass_%d",i)  , Form("h2D_pairDecayL_pairMass_%d",i)  , 100,0,30,1000,0.45,0.55             )       ) ;
		h2D_p1Pt_pairMass.push_back(        new TH2D( Form("h2D_p1Pt_pairMass.%d",i)        , Form("h2D_p1Pt_pairMass.%d",i)        , 100,0,10,1000,0.45,0.55             )       ) ;
		h2D_p2Pt_pairMass.push_back(        new TH2D( Form("h2D_p2Pt_pairMass.%d",i)        , Form("h2D_p2Pt_pairMass.%d",i)        , 100,0,10,1000,0.45,0.55             )       ) ;
	}

	double delta_Cali_scale = (Cali_scale_max - Cali_scale_min)/10.;
	std::vector<double> Cali_scale;
	std::vector<double> Cali_n; 
	for(int i =0 ; i < (Cali_NPoint +1) ;i ++){
		Cali_scale.push_back( Cali_scale_min + i * delta_Cali_scale  );
		Cali_n.push_back(i);
	}

	gr_ScaleFactor = new TGraph( Cali_NPoint+1, Cali_n.data(), Cali_scale.data() );
	


}



void ntp_K0s_Histogram::Fill_EventInfo(){
		h1D_Vz     				->Fill(Reader->Vz);
		for(int i =0; i < Reader->mNTrigs;i++){
			if(Reader->mTrigId[i] == 910001 )     {h1D_TrigID->Fill(1);}
			else if(Reader->mTrigId[i] == 910003) {h1D_TrigID->Fill(2);}
			else if(Reader->mTrigId[i] == 910013) {h1D_TrigID->Fill(3);}
			else if(Reader->mTrigId[i] == 910802) {h1D_TrigID->Fill(4);}
			else if(Reader->mTrigId[i] == 910804) {h1D_TrigID->Fill(5);}
			else {h1D_TrigID->Fill(6);}
		}
	
}

void ntp_K0s_Histogram::Fill_K0sInfo(int pair_Charge, float pair_DauDCA, float pair_Theta, float pair_DecayL){
		
		h1D_pair_Charge ->Fill(pair_Charge);
		h1D_pair_DauDCA ->Fill(pair_DauDCA);
		h1D_pair_CosTheta->Fill(TMath::Cos(pair_Theta)  ) ;
		h1D_pair_DecayL ->Fill(pair_DecayL);
		h1D_pair_DCA    ->Fill(pair_DecayL*TMath::Sin(pair_Theta) );

	



		
	
}


void ntp_K0s_Histogram::Fill_K0sInfo(int i_scale, TLorentzVector K0s_scaled,float pair_DecayL){
		h2D_pair_Pt     ->Fill(i_scale, K0s_scaled.Pt()  );
		h2D_pair_Eta    ->Fill(i_scale, K0s_scaled.Eta() );
		h2D_pair_Phi    ->Fill(i_scale, K0s_scaled.Phi() );
		h2D_pair_Mass   ->Fill(i_scale, K0s_scaled.M()   );

		
	



		
		h1D_pair_Mass[i_scale]->Fill( K0s_scaled.M() );
		h2D_pairPt_pairMass[i_scale]->Fill( K0s_scaled.Pt(),K0s_scaled.M() );
		h2D_pairEta_pairMass[i_scale]->Fill( K0s_scaled.Eta(),K0s_scaled.M() );
		h2D_pairPhi_pairMass[i_scale]->Fill( K0s_scaled.Phi(),K0s_scaled.M() );
		h2D_pairDecayL_pairMass[i_scale]->Fill(  pair_DecayL ,K0s_scaled.M() );
			
		
	
}



void ntp_K0s_Histogram::Fill_DauPionInfo(float p1_Eta,float p1_Phi ,float p1_Dca, float p1_Dcaxy, float p1_nSigmaPion ,float p2_Eta,float p2_Phi ,float p2_Dca, float p2_Dcaxy, float p2_nSigmaPion){
		
		
		h1D_p1_Eta     	->Fill( p1_Eta );
		h1D_p1_Phi     	->Fill( p1_Phi);
		h1D_p1_Dca    	->Fill( p1_Dca );
		h1D_p1_Dcaxy  	->Fill( p1_Dcaxy);
		h1D_p1_nSigmaPion ->Fill( p1_nSigmaPion );

		
		h1D_p2_Eta     	->Fill(p2_Eta);
		h1D_p2_Phi    	->Fill(p2_Phi);
		h1D_p2_Dca     	->Fill(p2_Dca);
		h1D_p2_Dcaxy    ->Fill(p2_Dcaxy);
		h1D_p2_nSigmaPion ->Fill(p2_nSigmaPion);



		
	
}


void ntp_K0s_Histogram::Fill_DauPionInfo(int i_scale, TLorentzVector K0s_scaled,TLorentzVector Pion1_scaled,TLorentzVector Pion2_scaled){
		
		h2D_p1_Pt  		->Fill( i_scale,Pion1_scaled.Pt() );
		

		h2D_p2_Pt 		->Fill(i_scale,Pion2_scaled.Pt() );
		



		
		
		h2D_p1Pt_pairMass[i_scale]->Fill(Pion1_scaled.Pt(),K0s_scaled.M());
		h2D_p2Pt_pairMass[i_scale]->Fill(Pion2_scaled.Pt(),K0s_scaled.M());
		
	
}


















void ntp_K0s_Histogram::Reset(){
	

	h1D_Vz 			->Reset("ICES");	
	h1D_TrigID		->Reset("ICES");	

	h2D_pair_Pt     ->Reset("ICES");
	h2D_pair_Eta    ->Reset("ICES");
	h2D_pair_Phi    ->Reset("ICES");
	h2D_pair_Mass   ->Reset("ICES");

	h1D_pair_Charge ->Reset("ICES");
	h1D_pair_DauDCA ->Reset("ICES");
	h1D_pair_CosTheta->Reset("ICES");
	h1D_pair_DecayL->Reset("ICES");
	h1D_pair_DCA    ->Reset("ICES");

	h2D_p1_Pt  		->Reset("ICES");
	h1D_p1_Eta     	->Reset("ICES");
	h1D_p1_Phi     	->Reset("ICES");
	h1D_p1_Dca    	->Reset("ICES");
	h1D_p1_Dcaxy  	->Reset("ICES");
	h1D_p1_nSigmaPion ->Reset("ICES");

	h2D_p2_Pt 		->Reset("ICES");
	h1D_p2_Eta     	->Reset("ICES");
	h1D_p2_Phi    	->Reset("ICES");
	h1D_p2_Dca     	->Reset("ICES");
	h1D_p2_Dcaxy   	->Reset("ICES");
	h1D_p2_nSigmaPion ->Reset("ICES");



	for(int i =0 ; i <Cali_NPoint+1 ;i++){
		h1D_pair_Mass[i]->Reset("ICES");
		h2D_pairPt_pairMass[i]->Reset("ICES");
		h2D_pairEta_pairMass[i]->Reset("ICES");
		h2D_pairPhi_pairMass[i]->Reset("ICES");
		h2D_pairDecayL_pairMass[i]->Reset("ICES");
		h2D_p1Pt_pairMass   [i]->Reset("ICES");
		h2D_p2Pt_pairMass[i]->Reset("ICES");
	}



	gr_ScaleFactor->Reset();
	




	
}

void ntp_K0s_Histogram::WriteAll(){
	TFile *fout= TFile::Open(OutPutFile.c_str(),"RECREATE");

	
	h1D_Vz 			->Write();	
	h1D_TrigID		->Write();	

	h2D_pair_Pt     ->Write();
	h2D_pair_Eta    ->Write();
	h2D_pair_Phi    ->Write();
	h2D_pair_Mass   ->Write();

	h1D_pair_Charge ->Write();
	h1D_pair_DauDCA ->Write();
	h1D_pair_CosTheta->Write();
	h1D_pair_DecayL->Write();
	h1D_pair_DCA    ->Write();

	h2D_p1_Pt  		->Write();
	h1D_p1_Eta     	->Write();
	h1D_p1_Phi     	->Write();
	h1D_p1_Dca    	->Write();
	h1D_p1_Dcaxy  	->Write();
	h1D_p1_nSigmaPion ->Write();

	h2D_p2_Pt 		->Write();
	h1D_p2_Eta     	->Write();
	h1D_p2_Phi    	->Write();
	h1D_p2_Dca     	->Write();
	h1D_p2_Dcaxy   	->Write();
	h1D_p2_nSigmaPion ->Write();



	for(int i =0 ; i <Cali_NPoint+1 ;i++){
		h1D_pair_Mass[i]->Write();
		h2D_pairPt_pairMass[i]->Write();
		h2D_pairEta_pairMass[i]->Write();
		h2D_pairPhi_pairMass[i]->Write();
		h2D_pairDecayL_pairMass[i]->Write();
		h2D_p1Pt_pairMass   [i]->Write();
		h2D_p2Pt_pairMass[i]->Write();
	}

	gr_ScaleFactor->Write();

	fout->Close();
	delete fout;
	
	
	
	

}






#endif 
