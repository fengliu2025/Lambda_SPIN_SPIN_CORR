#ifndef ntp_Lambda_Histogram_h
#define ntp_Lambda_Histogram_h

//include the header file here 
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TMath.h>
#include <TLorentzVector.h>


#include <string>
#include <iostream>


#include "ntp_Lambda_Reader.h"


#include "constants.h"
class ntp_Lambda_Histogram {
public : 
	ntp_Lambda_Reader *Reader;

	std::string OutPutFile;

	//Histograms for QA plot
	//QA plots. Basics Distribution of daughter particles.(After Selection).

	TH1D *h1D_Vz;
	TH1D *h1D_NLambda; 
	TH1D *h1D_TrigID;

	TH2D *h2D_NLambda_Ntrks;

	TH1D *h1D_high_Pt;
	TH1D *h1D_high_Phi;
	TH1D *h1D_high_eta;



	TH1D *h1D_pair_Pt;
	TH1D *h1D_pair_Eta;
	TH1D *h1D_pair_Phi;
	TH1D *h1D_pair_Mass;
	TH1D *h1D_pair_Charge;
	TH1D *h1D_pair_DauDCA;
	TH1D *h1D_pair_CosTheta;
	TH1D *h1D_pair_DecayL;
	TH1D *h1D_pair_DCA;

	TH1D *h1D_p1_Pt;
	TH1D *h1D_p1_Eta;
	TH1D *h1D_p1_Phi;
	TH1D *h1D_p1_Dca;

	TH1D *h1D_p2_Pt;
	TH1D *h1D_p2_Eta;
	TH1D *h1D_p2_Phi;
	TH1D *h1D_p2_Dca;



	TH2D *h2D_NLambda_NGoodLambda; 
	TH1D *h2D_NLambda_PtDiff[3];
	TH2D *h2D_NLambda_RapidityDiff[3];
	TH2D *h2D_NLambda_PhiDiff[3];
	TH2D *h2D_NLambda_DeltaR[3];

	
	



	ntp_Lambda_Histogram();
	ntp_Lambda_Histogram(ntp_Lambda_Reader *reader,std::string outPutFile);
	void InitHitogram();
	void Fill_QAplots();
	void Fill_QAplots(std::vector<int> GoodLambdaFlag);
	void Fill_PairPlots(TLorentzVector *v1,TLorentzVector *v2, int pair_type);
	void Fill_NLambda_NGoodLambda(int NGoodLambda);
	void Reset();

	void WriteAll();

};

ntp_Lambda_Histogram::ntp_Lambda_Histogram()
{}

ntp_Lambda_Histogram::ntp_Lambda_Histogram(ntp_Lambda_Reader *reader,std::string outPutFile)
:Reader(reader),OutPutFile(outPutFile)
{

}

void ntp_Lambda_Histogram::InitHitogram(){
	TH1::SetDefaultSumw2(kTRUE);

	h1D_Vz         = new TH1D("h1D_Vz","h1D_vz",200,-100,100);
	h1D_NLambda    = new TH1D("h1D_NLambda","h1D_NLambda",10,-1,9);
	h1D_TrigID     = new TH1D("h1D_TrigID","h1D_TrigID",6,0.5,6.5);

	h2D_NLambda_Ntrks = new TH2D("h2D_NLambda_Ntrks","h2D_NLambda_Ntrks",10,-1,9,100,-1,99);



	h1D_high_Pt    = new TH1D("h1D_high_Pt","h1D_high_Pt",100,-1,10);
	h1D_high_Phi   = new TH1D("h1D_high_Phi","h1D_high_Phi",100,-2*TMath::Pi(), 2 * TMath::Pi() );
	h1D_high_eta   = new TH1D("h1D_high_eta","h1D_high_eta",100,-4,4);

	h1D_pair_Pt    = new TH1D("h1D_pair_Pt","h1D_pair_Pt",100,0,10);
	h1D_pair_Eta   = new TH1D("h1D_pair_Eta","h1D_pair_Eta",100,-3,3);
	h1D_pair_Phi   = new TH1D("h1D_pair_Phi","h1D_pair_Phi",100,-2*TMath::Pi(),2*TMath::Pi());
	h1D_pair_Mass  = new TH1D("h1D_pair_Mass","h1D_pair_Mass",120,1.07,1.20);
	h1D_pair_Charge= new TH1D("h1D_pair_Charge","h1D_pair_Charge",4,-2,2);
	h1D_pair_DauDCA= new TH1D("h1D_pair_DauDCA","h1D_pair_DauDCA",100,-5,5);
	h1D_pair_CosTheta= new TH1D("h1D_pair_CosTheta","h1D_pair_CosTheta",100,0.5,1.5);
	h1D_pair_DecayL = new TH1D("h1D_piar_DecayL","h1D_pair_DecayL",100,0,30);
	h1D_pair_DCA    = new TH1D("h1D_pair_DCA","h1D_pair_DCA",100,-2,2);




	h1D_p1_Pt      = new TH1D("h1D_p1_Pt","h1D_p1_Pt",100,0,10);
	h1D_p1_Eta     = new TH1D("h1D_p1_Eta","h1D_p1_Eta",100,-3,3); 
	h1D_p1_Phi     = new TH1D("h1D_p1_Phi","h1D_p1_Phi",100,-2*TMath::Pi(),2*TMath::Pi() ); 
	h1D_p1_Dca     = new TH1D("h1D_p1_Dca","h1D_p1_Dca",100,-1,1);


	h1D_p2_Pt      = new TH1D("h1D_p2_Pt","h1D_p2_Pt",100,0,10);
	h1D_p2_Eta     = new TH1D("h1D_p2_Eta","h1D_p2_Eta",100,-3,3);
	h1D_p2_Phi     = new TH1D("h1D_p2_Phi","h1D_p2_Phi",100,-2*TMath::Pi(),2*TMath::Pi() ); 
	h1D_p2_Dca     = new TH1D("h1D_p2_Dca","h1D_p2_Dca",100,-1,1);


	
	TH2D *h2D_NLambda_NGoodLambda = new TH2D("h2D_NLambda_NGoodLambda","h2D_NLambda_NGoodLambda",10,0.5,10.5,11,-0.5,10.5); 
	
	for(int i =0 ; i < 3 ; i ++){
		h2D_NLambda_PtDiff[i]        = new TH2D(Form("h2D_NLambda_PtDiff_%d",i),Form("h2D_NLambda_PtDiff_%d",i),10,0.5,10.5,100,-10,10 );
		h2D_NLambda_RapidityDiff[i]  = new TH2D(Form("h2D_NLambda_RapidityDiff_%d",i),Form("h2D_NLambda_RapidityDiff_%d",i),10,0.5,10.5,100,-5,5);
		h2D_NLambda_PhiDiff[i]       = new TH2D(Form("h2D_NLambda_PhiDiff_%d",i),Form("h2D_NLambda_PhiDiff_%d",i),10,0.5,10.5,200,-2*TMath::Pi(),2*TMath::Pi());
		h2D_NLambda_DeltaR[i]        = new TH2D(Form("h2D_NLambda_DeltaR_%d",i),Form("h2D_NLambda_DeltaR_%d",i),10,0.5,10.5,100,0,4 );

	}
	
	
	

	
	



}



void ntp_Lambda_Histogram::Fill_QAplots(){
		h1D_Vz     				->Fill(Reader->Vz);
		h1D_NLambda     		->Fill(Reader->NLambda);
		for(int i =0; i < Reader->mNTrigs;i++){
			if(Reader->mTrigId[i] == 910001 )     {h1D_TrigID->Fill(1);}
			else if(Reader->mTrigId[i] == 910003) {h1D_TrigID->Fill(2);}
			else if(Reader->mTrigId[i] == 910013) {h1D_TrigID->Fill(3);}
			else if(Reader->mTrigId[i] == 910802) {h1D_TrigID->Fill(4);}
			else if(Reader->mTrigId[i] == 910804) {h1D_TrigID->Fill(5);}
			else {h1D_TrigID->Fill(6);}
		}

		

		
		h2D_NLambda_Ntrks->Fill(Reader->NLambda,Reader->mNTrks);

		for(int i =0 ; i < Reader->mNTrks;i++){
			h1D_high_Pt   ->Fill(Reader->high_pt[i]  );
			h1D_high_Phi  ->Fill(Reader->high_phi[i] );
			h1D_high_eta  ->Fill(Reader->high_eta[i] );
		}

		for(int i =0 ; i < Reader->NLambda;i++){
			h1D_pair_Pt     	->Fill(Reader->pair_pt[i]);
			h1D_pair_Eta    	->Fill(Reader->pair_eta[i]);
			h1D_pair_Phi  		->Fill(Reader->pair_phi[i]);
			h1D_pair_Mass   	->Fill(Reader->pair_mass[i]);
			h1D_pair_Charge 	->Fill(Reader->pair_charge[i]);
			h1D_pair_DauDCA 	->Fill(Reader->pair_DCAdaughters[i]);
			h1D_pair_CosTheta	->Fill(TMath::Cos(Reader->pair_theta[i] ) );
			h1D_pair_DecayL 	->Fill(Reader->pair_decayL[i]);
			h1D_pair_DCA   		->Fill(Reader->pair_decayL[i] * TMath::Sin(Reader->pair_theta[i]) );




			h1D_p1_Pt   		->Fill(Reader->p1_pt[i]);  
			h1D_p1_Eta    		->Fill(Reader->p1_eta[i]);
			h1D_p1_Phi    		->Fill(Reader->p1_phi[i]);
			h1D_p1_Dca    		->Fill(Reader->p1_dca[i]);


			h1D_p2_Pt       	->Fill(Reader->p2_pt[i]);
			h1D_p2_Eta   		->Fill(Reader->p2_eta[i]);
			h1D_p2_Phi     		->Fill(Reader->p2_phi[i]);
			h1D_p2_Dca    		->Fill(Reader->p2_dca[i]);
		}

	
}


void ntp_Lambda_Histogram::Fill_QAplots(std::vector<int> GoodLambdaFlag){
		h1D_Vz     				->Fill(Reader->Vz);
		h1D_NLambda     		->Fill(Reader->NLambda);
		for(int i =0; i < Reader->mNTrigs;i++){
			if(Reader->mTrigId[i] == 910001 )     {h1D_TrigID->Fill(1);}
			else if(Reader->mTrigId[i] == 910003) {h1D_TrigID->Fill(2);}
			else if(Reader->mTrigId[i] == 910013) {h1D_TrigID->Fill(3);}
			else if(Reader->mTrigId[i] == 910802) {h1D_TrigID->Fill(4);}
			else if(Reader->mTrigId[i] == 910804) {h1D_TrigID->Fill(5);}
			else {h1D_TrigID->Fill(6);}
		}

		

		
		h2D_NLambda_Ntrks->Fill(Reader->NLambda,Reader->mNTrks);

		for(int i =0 ; i < Reader->mNTrks;i++){
			h1D_high_Pt   ->Fill(Reader->high_pt[i]  );
			h1D_high_Phi  ->Fill(Reader->high_phi[i] );
			h1D_high_eta  ->Fill(Reader->high_eta[i] );
		}

		for(int i =0 ; i < Reader->NLambda;i++){
			if(GoodLambdaFlag[i]==0) continue;
			h1D_pair_Pt     	->Fill(Reader->pair_pt[i]);
			h1D_pair_Eta    	->Fill(Reader->pair_eta[i]);
			h1D_pair_Phi  		->Fill(Reader->pair_phi[i]);
			h1D_pair_Mass   	->Fill(Reader->pair_mass[i]);
			h1D_pair_Charge 	->Fill(Reader->pair_charge[i]);
			h1D_pair_DauDCA 	->Fill(Reader->pair_DCAdaughters[i]);
			h1D_pair_CosTheta	->Fill(TMath::Cos(Reader->pair_theta[i] ) );
			h1D_pair_DecayL 	->Fill(Reader->pair_decayL[i]);
			h1D_pair_DCA   		->Fill(Reader->pair_decayL[i] * TMath::Sin(Reader->pair_theta[i]) );




			h1D_p1_Pt   		->Fill(Reader->p1_pt[i]);  
			h1D_p1_Eta    		->Fill(Reader->p1_eta[i]);
			h1D_p1_Phi    		->Fill(Reader->p1_phi[i]);
			h1D_p1_Dca    		->Fill(Reader->p1_dca[i]);


			h1D_p2_Pt       	->Fill(Reader->p2_pt[i]);
			h1D_p2_Eta   		->Fill(Reader->p2_eta[i]);
			h1D_p2_Phi     		->Fill(Reader->p2_phi[i]);
			h1D_p2_Dca    		->Fill(Reader->p2_dca[i]);
		}

	
}



void ntp_Lambda_Histogram::Fill_PairPlots(TLorentzVector *v1,TLorentzVector *v2, int pair_type){
	double delta_Rapidity = v1->Rapidity() - v2->Rapidity();
	double delta_Phi = TMath::ACos( TMath::Cos( v1->Phi() - v2->Phi() ) );
	double delta_Pt  = v1->Pt() - v2->Pt();
	double deltaR = TMath::Sqrt( delta_Phi * delta_Phi + delta_y * delta_y  );


	TH1D *h2D_NLambda_PtDiff[pair_type]->Fill(Reader->NLambda,delta_Pt);
	TH2D *h2D_NLambda_RapidityDiff[pair_type]->Fill(Reader->NLambda,delta_Rapidity);
	TH2D *h2D_NLambda_PhiDiff[pair_type]->Fill(Reader->NLambda,delta_Phi);
	TH2D *h2D_NLambda_DeltaR[pair_type]->Fill(Reader->NLambda,deltaR);


}




void ntp_Lambda_Histogram::Fill_NLambda_NGoodLambda(int NGoodLambda){
	h2D_NLambda_NGoodLambda->Fill(Reader->NLambda,NGoodLambda);
}









void ntp_Lambda_Histogram::Reset(){
	

	
	h1D_Vz         		->Reset("ICES");
	h1D_NLambda    		->Reset("ICES");
	h1D_TrigID     		->Reset("ICES");

	h2D_NLambda_Ntrks   ->Reset("ICES");

	h1D_high_Pt   		->Reset("ICES");
	h1D_high_Phi 		->Reset("ICES");
	h1D_high_eta 		->Reset("ICES");

	h1D_pair_Pt    		->Reset("ICES");
	h1D_pair_Eta    	->Reset("ICES");
	h1D_pair_Phi    	->Reset("ICES");
	h1D_pair_Mass   	->Reset("ICES");
	h1D_pair_Charge 	->Reset("ICES");
	h1D_pair_DauDCA 	->Reset("ICES");
	h1D_pair_CosTheta	->Reset("ICES");
	h1D_pair_DecayL		->Reset("ICES");
	h1D_pair_DCA   		->Reset("ICES");




	h1D_p1_Pt     		->Reset("ICES");
	h1D_p1_Eta    		->Reset("ICES");
	h1D_p1_Phi    		->Reset("ICES");
	h1D_p1_Dca    		->Reset("ICES");


	h1D_p2_Pt     		->Reset("ICES");
	h1D_p2_Eta    		->Reset("ICES");
	h1D_p2_Phi    		->Reset("ICES");
	h1D_p2_Dca    		->Reset("ICES");


	h2D_NLambda_NGoodLambda ->Reset("ICES");
	for(int i =0 ; i <3 ; i++){
		h2D_NLambda_PtDiff[i]->Reset("ICES");
		h2D_NLambda_RapidityDiff[i]->Reset("ICES");
		h2D_NLambda_PhiDiff[i]->Reset("ICES");
		h2D_NLambda_DeltaR[i]->Reset("ICES");
	}
	

	

	
}

void ntp_Lambda_Histogram::WriteAll(){
	TFile *fout= TFile::Open(OutPutFile.c_str(),"RECREATE");

	
	h1D_Vz         		->Write();
	h1D_NLambda    		->Write();
	h1D_TrigID     		->Write();


	h2D_NLambda_Ntrks   ->Write();

	h1D_high_Pt   		->Write();
	h1D_high_Phi 		->Write();
	h1D_high_eta 		->Write();


	h1D_pair_Pt    		->Write();
	h1D_pair_Eta    	->Write();
	h1D_pair_Phi    	->Write();
	h1D_pair_Mass   	->Write();
	h1D_pair_Charge 	->Write();
	h1D_pair_DauDCA 	->Write();
	h1D_pair_CosTheta	->Write();
	h1D_pair_DecayL		->Write();
	h1D_pair_DCA   		->Write();




	h1D_p1_Pt     		->Write();
	h1D_p1_Eta    		->Write();
	h1D_p1_Phi    		->Write();
	h1D_p1_Dca    		->Write();


	h1D_p2_Pt     		->Write();
	h1D_p2_Eta    		->Write();
	h1D_p2_Phi    		->Write();
	h1D_p2_Dca    		->Write();



	h2D_NLambda_NGoodLambda->Write(); 
	for(int i =0 ; i <3 ; i++){
		h2D_NLambda_PtDiff[i]->Write();
		h2D_NLambda_RapidityDiff[i]->Write();
		h2D_NLambda_PhiDiff[i]->Write();
		h2D_NLambda_DeltaR[i]->Write();
	}
	
	

	fout->Close();
	delete fout;
	

	
	

}






#endif 
