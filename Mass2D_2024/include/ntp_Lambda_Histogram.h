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


#include "ntp_Lambda_Reader_v3.h"


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
	TH1D *h1D_p1_Dcaxy;
	TH1D *h1D_p1_nSigmaProton;

	TH1D *h1D_p2_Pt;
	TH1D *h1D_p2_Eta;
	TH1D *h1D_p2_Phi;
	TH1D *h1D_p2_Dca;
	TH1D *h1D_p2_Dcaxy;
	TH1D *h1D_p2_nSigmaPion;



	TH1D *h1D_track_Number;
	TH1D *h1D_track_pt;
	TH1D *h1D_track_eta;
	TH1D *h1D_track_phi;
	TH1D *h1D_track_dca;
	TH1D *h1D_track_dcaxy;
	TH1D *h1D_track_nSigmaPion;
	TH1D *h1D_track_nSigmaKaon;
	TH1D *h1D_track_nSigmaProton;
	TH1D *h1D_track_ch;

	TH2D *h2D_NLambda_NGoodLambda; 
	TH2D *h2D_NLambda_PtDiff[3];
	TH2D *h2D_NLambda_RapidityDiff[3];
	TH2D *h2D_NLambda_PhiDiff[3];
	TH2D *h2D_NLambda_DeltaR[3];

	TH2D *h2D_DeltaR_NTrksInWindow[3];

	TH2D *h2D_NLambda_pairMass[2];
	TH2D *h2D_pairPt_pairMass[2];
	TH2D *h2D_pairEta_pairMass[2];
	TH2D *h2D_pairPhi_pairMass[2];
	TH2D *h2D_pairDecayL_pairMass[2];
	TH2D *h2D_p1Pt_pairMass[2];
	TH2D *h2D_p2Pt_pairMass[2];
	TH2D *h2D_p1Pt_p2Pt[2];

	TH1D *h1D_p1_plus_pt;
	TH1D *h1D_p1_minus_pt;
	TH1D *h1D_p2_plus_pt;
	TH1D *h1D_p2_minus_pt;

	TH2D *h2D_Lambda_LambdaBar_US_US[2][2];
	TH2D *h2D_Lambda_LambdaBar_US_LS[2][2];
	TH2D *h2D_Lambda_Lambda_US_US[2][2];
	TH2D *h2D_Lambda_Lambda_US_LS[2][2];
	TH2D *h2D_LambdaBar_LambdaBar_US_US[2][2];
	TH2D *h2D_LambdaBar_LambdaBar_US_LS[2][2];


	TH2D *h2D_Lambda_LambdaBar_US_US_DeltaR[Range_Bin] ;
	TH2D *h2D_Lambda_LambdaBar_US_LS_DeltaR[Range_Bin] ;
	TH2D *h2D_Lambda_Lambda_US_US_DeltaR[Range_Bin]   ;
	TH2D *h2D_Lambda_Lambda_US_LS_DeltaR[Range_Bin]    ;
	TH2D *h2D_LambdaBar_LambdaBar_US_US_DeltaR[Range_Bin];
	TH2D *h2D_LambdaBar_LambdaBar_US_LS_DeltaR[Range_Bin];
	





	ntp_Lambda_Histogram();
	ntp_Lambda_Histogram(ntp_Lambda_Reader *reader,std::string outPutFile);
	void InitHitogram();
	void Fill_QAplots();
	void Fill_QAplots(std::vector<int> GoodLambdaFlag);
	void Fill_PairPlots(TLorentzVector *v1,TLorentzVector *v2, int pair_type);
	void Fill_Mass2D(int i_lambda,int j_lambda);
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

	h2D_NLambda_Ntrks = new TH2D("h2D_NLambda_Ntrks","h2D_NLambda_Ntrks",10,-1,9,100,-0.5,99.5);



	h1D_high_Pt    = new TH1D("h1D_high_Pt","h1D_high_Pt",100,-1,10);
	h1D_high_Phi   = new TH1D("h1D_high_Phi","h1D_high_Phi",100,-2*TMath::Pi(), 2 * TMath::Pi() );
	h1D_high_eta   = new TH1D("h1D_high_eta","h1D_high_eta",100,-4,4);

	h1D_pair_Pt    = new TH1D("h1D_pair_Pt","h1D_pair_Pt",100,0,10);
	h1D_pair_Eta   = new TH1D("h1D_pair_Eta","h1D_pair_Eta",100,-3,3);
	h1D_pair_Phi   = new TH1D("h1D_pair_Phi","h1D_pair_Phi",100,-2*TMath::Pi(),2*TMath::Pi());
	//h1D_pair_Mass  = new TH1D("h1D_pair_Mass","h1D_pair_Mass",120,1.07,1.20);
	h1D_pair_Mass  = new TH1D("h1D_pair_Mass","h1D_pair_Mass",1000,1.06,1.18);
	h1D_pair_Charge= new TH1D("h1D_pair_Charge","h1D_pair_Charge",4,-2,2);
	h1D_pair_DauDCA= new TH1D("h1D_pair_DauDCA","h1D_pair_DauDCA",100,-5,5);
	h1D_pair_CosTheta= new TH1D("h1D_pair_CosTheta","h1D_pair_CosTheta",100,0.5,1.5);
	h1D_pair_DecayL = new TH1D("h1D_piar_DecayL","h1D_pair_DecayL",100,0,30);
	h1D_pair_DCA    = new TH1D("h1D_pair_DCA","h1D_pair_DCA",100,-2,2);




	h1D_p1_Pt      = new TH1D("h1D_p1_Pt","h1D_p1_Pt",100,0,10);
	h1D_p1_Eta     = new TH1D("h1D_p1_Eta","h1D_p1_Eta",100,-3,3); 
	h1D_p1_Phi     = new TH1D("h1D_p1_Phi","h1D_p1_Phi",100,-2*TMath::Pi(),2*TMath::Pi() ); 
	h1D_p1_Dca     = new TH1D("h1D_p1_Dca","h1D_p1_Dca",100,-1,1);
	h1D_p1_Dcaxy   = new TH1D("h1D_p1_Dcaxy","h1D_p1_Dcaxy",100,-1,1);
	h1D_p1_nSigmaProton = new TH1D("h1D_p1_nSigmaProton","h1D_p1_nSigmaProton",100,-5,5);

	h1D_p2_Pt      = new TH1D("h1D_p2_Pt","h1D_p2_Pt",100,0,10);
	h1D_p2_Eta     = new TH1D("h1D_p2_Eta","h1D_p2_Eta",100,-3,3);
	h1D_p2_Phi     = new TH1D("h1D_p2_Phi","h1D_p2_Phi",100,-2*TMath::Pi(),2*TMath::Pi() ); 
	h1D_p2_Dca     = new TH1D("h1D_p2_Dca","h1D_p2_Dca",100,-1,1);
	h1D_p2_Dcaxy   = new TH1D("h1D_p2_Dcaxy","h1D_p2_Dcaxy",100,-1,1);
	h1D_p2_nSigmaPion = new TH1D("h1D_p2_nSigmaPion","h1D_p2_nSigmaPion",100,-5,5);






	h1D_track_Number = new TH1D("h1D_track_Number","h1D_track_Number",100,0.5,100.5);
	h1D_track_pt     = new TH1D("h1D_track_pt","h1D_track_pt",200,0,5);
	h1D_track_eta	 = new TH1D("h1D_track_eta","h1D_track_eta",200,-2,2);
	h1D_track_phi	 = new TH1D("h1D_track_phi","h1D_track_phi",200,-2*TMath::Pi(),2*TMath::Pi());
	h1D_track_dca    = new TH1D("h1D_track_dca","h1D_tracK_dca",200,-2,2);
	h1D_track_dcaxy  = new TH1D("h1D_track_dcaxy","h1D_track_dcaxy",200,-2,2);
	h1D_track_nSigmaPion = new TH1D("h1D_track_nSigmaPion","h1D_track_nSigmaPion",200,-5,5);
	h1D_track_nSigmaKaon = new TH1D("h1D_tracK_nSigmaKaon","h1D_track_nSigmaKaon",200,-5,5);
	h1D_track_nSigmaProton = new TH1D("h1D_track_nSigmaProton","h1D_track_nSigmaProton",200,-5,5);
	h1D_track_ch   = new TH1D("h1D_track_ch","h1D_track_ch",5,-2.5,2.5);





	
	h2D_NLambda_NGoodLambda = new TH2D("h2D_NLambda_NGoodLambda","h2D_NLambda_NGoodLambda",10,0.5,10.5,11,-0.5,10.5); 
	
	TH2D *h2D_DeltaR_NTrks[3];

	for(int i =0 ; i < 3 ; i ++){
		h2D_NLambda_PtDiff[i]        = new TH2D(Form("h2D_NLambda_PtDiff_%d",i),Form("h2D_NLambda_PtDiff_%d",i),10,0.5,10.5,100,-10,10 );
		h2D_NLambda_RapidityDiff[i]  = new TH2D(Form("h2D_NLambda_RapidityDiff_%d",i),Form("h2D_NLambda_RapidityDiff_%d",i),10,0.5,10.5,100,-5,5);
		h2D_NLambda_PhiDiff[i]       = new TH2D(Form("h2D_NLambda_PhiDiff_%d",i),Form("h2D_NLambda_PhiDiff_%d",i),10,0.5,10.5,200,-2*TMath::Pi(),2*TMath::Pi());
		h2D_NLambda_DeltaR[i]        = new TH2D(Form("h2D_NLambda_DeltaR_%d",i),Form("h2D_NLambda_DeltaR_%d",i),10,0.5,10.5,100,0,4 );
		h2D_DeltaR_NTrksInWindow[i]          = new TH2D(Form("h2D_DeltaR_NTrks_%d",i)  ,Form("h2D_DeltaR_NTrks_%d",i)  ,100,0,4,100,-0.5,99.5 );
	}
	
	
	
	for(int i=0 ;i <2 ;i++){
		h2D_NLambda_pairMass[i] 	= new TH2D(Form("h2D_NLambda_pairMass_%d",i), Form("h2D_NLambda_pairMass_%d",i),10,0.5,10.5,240,1.09,1.15);
		h2D_pairPt_pairMass[i]  	= new TH2D(Form("h2D_pairPt_pairMass_%d",i),  Form("h2D_pairPt_pairMass_%d",i),100,0,5,240,1.09,1.15);
		h2D_pairEta_pairMass[i] 	= new TH2D(Form("h2D_pairEta_pairMass_%d",i), Form("h2D_pairEta_pairMass_%d",i),200,-2,2,240,1.09,1.15);
		h2D_pairPhi_pairMass[i] 	= new TH2D(Form("h2D_pairPhi_PairMass_%d",i), Form("h2D_pairPhi_pair_Mass_%d",i),100,-3.2,3.2,240,1.09,1.15);
		h2D_pairDecayL_pairMass[i]  = new TH2D(Form("h2D_pairDecayL_pairMass_%d",i),Form("h2D_pairDecayL_pairMass_%d",i),100,2,25,240,1.09,1.15 );
		h2D_p1Pt_pairMass[i]		= new TH2D(Form("h2D_p1Pt_pairMass_%d",i)   , Form("h2D_p1Pt_pairMass_%d",i),100,0.15,5,240,1.09,1.15  );
		h2D_p2Pt_pairMass[i]		= new TH2D(Form("h2D_p2Pt_pairMass_%d",i)   , Form("h2D_p2Pt_pairMass_%d",i),100,0.15,1.5,240,1.09,1.15);
		h2D_p1Pt_p2Pt[i] 			= new TH2D(Form("h2D_p1Pt_p2Pt_%d",i)       , Form("h2D_p1Pt_p2Pt_%d",i)    ,200,0,5,200,0,3);
	}

	
	h1D_p1_plus_pt  = new TH1D("h1D_p1_plus_pt","h1D_p1_plus_pt",100,0,10);
	h1D_p1_minus_pt = new TH1D("h1D_p1_minus_pt","h1D_p1_minus_pt",100,0,10);
	h1D_p2_plus_pt  = new TH1D("h1D_p2_plus_pt","h1D_p2_plus_pt",100,0,10);
	h1D_p2_minus_pt = new TH1D("h1D_p2_minus_pt","h1D_p2_minus_pt",100,0,10);


	for(int i = 0 ;i < 2 ; i++ ){
		for(int j=0; j <2 ;j++){
			h2D_Lambda_LambdaBar_US_US[i][j] = new TH2D( Form("h2D_Lambda_LambdaBar_US_US_%d_%d",i,j),Form("h2D_Lambda_LambdaBar_US_US_%d_%d",i,j),1000,1.07,1.20, 1000,1.07,1.20  );
			h2D_Lambda_LambdaBar_US_LS[i][j] = new TH2D( Form("h2D_Lambda_LambdaBar_US_LS_%d_%d",i,j),Form("h2D_Lambda_LambdaBar_US_LS_%d_%d",i,j),1000,1.07,1.20, 1000,1.07,1,20  );
			h2D_Lambda_Lambda_US_US[i][j]    = new TH2D( Form("h2D_Lambda_Lambda_US_US_%d_%d",i,j)   ,Form("h2D_Lambda_Lambda_US_US_%d_%d",i,j)   ,1000,1.07,1.20, 1000,1.07,1.20  );
			h2D_Lambda_Lambda_US_LS[i][j]    = new TH2D( Form("h2D_Lambda_Lambda_US_LS_%d_%d",i,j)   ,Form("h2D_Lambda_Lambda_US_LS_%d_%d",i,j)   ,1000,1.07,1.20, 1000,1.07,1.20  );
			h2D_LambdaBar_LambdaBar_US_US[i][j] = new TH2D( Form("h2D_LambdaBar_LambdaBar_US_US_%d_%d",i,j), Form("h2D_LambdaBar_LambdaBar_%d_%d",i,j),1000,1.07,1.20,1000,1.07,1.20 );
			h2D_LambdaBar_LambdaBar_US_LS[i][j] = new TH2D( Form("h2D_LambdaBar_LambdaBar_US_LS_%d_%d",i,j), Form("h2D_LambdaBar_LambdaBar_%d_%d",i,j),1000,1.07,1.20,1000,1.07,1.20 );
		}
	}


	for(int i= 0 ;i < Range_Bin;i++){
		h2D_Lambda_LambdaBar_US_US_DeltaR[i] = new TH2D( Form("h2D_Lambda_LambdaBar_US_US_DeltaR_%d",i), Form("h2D_Lambda_LambdaBar_US_US_DeltaR_%d",i) , 1000,1.07,1.20, 1000, 1.07, 1.20 );
		h2D_Lambda_LambdaBar_US_LS_DeltaR[i] = new TH2D( Form("h2D_Lambda_LambdaBar_US_LS_DeltaR_%d",i), Form("h2D_Lambda_LambdaBar_US_LS_DeltaR_%d",i) , 1000,1.07,1.20, 1000, 1.07, 1.20 );
		h2D_Lambda_Lambda_US_US_DeltaR[i]    = new TH2D( Form("h2D_Lambda_Lambda_US_US_DeltaR_%d",i)   , Form("h2D_Lambda_Lambda_US_US_DeltaR_%d",i)    , 1000,1.07,1.20, 1000, 1.07, 1.20 );
		h2D_Lambda_Lambda_US_LS_DeltaR[i]    = new TH2D( Form("h2D_Lambda_Lambda_US_LS_DeltaR_%d",i)   , Form("h2D_Lambda_Lambda_US_LS_DeltaR_%d",i)    , 1000,1.07,1.20, 1000, 1.07, 1.20 );
		h2D_LambdaBar_LambdaBar_US_US_DeltaR[i] = new TH2D( Form("h2D_LambdaBar_LambdaBar_US_US_DeltaR_%d",i) , Form("h2D_LambdaBar_LambdaBar_US_US_DeltaR_%d",i) , 1000, 1.07, 1.20, 1000, 1.07, 1.20 );
		h2D_LambdaBar_LambdaBar_US_LS_DeltaR[i] = new TH2D( Form("h2D_LambdaBar_LambdaBar_US_LS_DeltaR_%d",i) , Form("h2D_LambdaBar_LambdaBar_US_LS_DeltaR_%d",i) , 1000, 1.07, 1.20, 1000, 1.07, 1.20 );
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

		

		
		h2D_NLambda_Ntrks->Fill(Reader->NLambda,Reader->track_Number);

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
			h1D_p1_Dcaxy    	->Fill(Reader->p1_dcaxy[i]);
			h1D_p1_nSigmaProton ->Fill(Reader->p1_nSigmaProton[i]);

			h1D_p2_Pt       	->Fill(Reader->p2_pt[i]);
			h1D_p2_Eta   		->Fill(Reader->p2_eta[i]);
			h1D_p2_Phi     		->Fill(Reader->p2_phi[i]);
			h1D_p2_Dca    		->Fill(Reader->p2_dca[i]);
			h1D_p2_Dcaxy    	->Fill(Reader->p2_dcaxy[i]);
			h1D_p2_nSigmaPion   ->Fill(Reader->p2_nSigmaPion[i]);




		}

		h1D_track_Number ->Fill(Reader->track_Number);

		for(int i =0 ; i < Reader->track_Number;i++){
			h1D_track_pt     ->Fill(Reader->track_pt[i]);
			h1D_track_eta	 ->Fill(Reader->track_eta[i]);
			h1D_track_phi	 ->Fill(Reader->track_phi[i]);
			h1D_track_dca    ->Fill(Reader->track_dca[i]);
			h1D_track_dcaxy  ->Fill(Reader->track_dcaxy[i]);
			h1D_track_nSigmaPion  ->Fill(Reader->track_nSigmaPion[i]);
			h1D_track_nSigmaKaon  ->Fill(Reader->track_nSigmaKaon[i]);
			h1D_track_nSigmaProton ->Fill(Reader->track_nSigmaProton[i]);
			h1D_track_ch ->Fill(Reader->track_ch[i]);
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
			h1D_p1_Dcaxy    	->Fill(Reader->p1_dcaxy[i]);
			h1D_p1_nSigmaProton ->Fill(Reader->p1_nSigmaProton[i]);

			h1D_p2_Pt       	->Fill(Reader->p2_pt[i]);
			h1D_p2_Eta   		->Fill(Reader->p2_eta[i]);
			h1D_p2_Phi     		->Fill(Reader->p2_phi[i]);
			h1D_p2_Dca    		->Fill(Reader->p2_dca[i]);
			h1D_p2_Dcaxy    	->Fill(Reader->p2_dcaxy[i]);
			h1D_p2_nSigmaPion   ->Fill(Reader->p2_nSigmaPion[i]);
		
	
		

			



			
			if(Reader->p1_ch[i] == 1) {
				h2D_NLambda_pairMass[0]->Fill( Reader->NLambda,Reader->pair_mass[i] );
				h2D_pairPt_pairMass[0] ->Fill( Reader->pair_pt[i],Reader->pair_mass[i]);
				h2D_pairEta_pairMass[0]->Fill( Reader->pair_eta[i],Reader->pair_mass[i]);
				h2D_pairPhi_pairMass[0]->Fill( Reader->pair_phi[i],Reader->pair_mass[i]);
				h2D_pairDecayL_pairMass[0]->Fill( Reader->pair_decayL[i],Reader->pair_mass[i] );
				h2D_p1Pt_pairMass[0]->Fill(Reader->p1_pt[i],Reader->pair_mass[i]);		
				h2D_p2Pt_pairMass[0]->Fill(Reader->p2_pt[i],Reader->pair_mass[i]);		
				h2D_p1Pt_p2Pt[0]    ->Fill(Reader->p1_pt[i] ,Reader->p2_pt[i]); 
				h1D_p1_plus_pt->Fill(Reader->p1_pt[i]);
				h1D_p2_minus_pt->Fill(Reader->p2_pt[i]);
			}
				
			
			if(Reader->p1_ch[i] == -1) {
				h2D_NLambda_pairMass[1]->Fill( Reader->NLambda,Reader->pair_mass[i] );
				h2D_pairPt_pairMass[1] ->Fill( Reader->pair_pt[i],Reader->pair_mass[i]);
				h2D_pairEta_pairMass[1]->Fill( Reader->pair_eta[i],Reader->pair_mass[i]);
				h2D_pairPhi_pairMass[1]->Fill( Reader->pair_phi[i],Reader->pair_mass[i]);
				h2D_pairDecayL_pairMass[1]->Fill( Reader->pair_decayL[i],Reader->pair_mass[i] );
				h2D_p1Pt_pairMass[1]->Fill(Reader->p1_pt[i],Reader->pair_mass[i]);		
				h2D_p2Pt_pairMass[1]->Fill(Reader->p2_pt[i],Reader->pair_mass[i]);
				h2D_p1Pt_p2Pt[1]    ->Fill(Reader->p1_pt[i] ,Reader->p2_pt[i]); 
				h1D_p1_minus_pt ->Fill(Reader->p1_pt[i]);
				h1D_p2_plus_pt->Fill(Reader->p2_pt[i]);		
			}
	

		}

		h1D_track_Number ->Fill(Reader->track_Number);

		for(int i =0 ; i < Reader->track_Number;i++){
			h1D_track_pt     ->Fill(Reader->track_pt[i]);
			h1D_track_eta	 ->Fill(Reader->track_eta[i]);
			h1D_track_phi	 ->Fill(Reader->track_phi[i]);
			h1D_track_dca    ->Fill(Reader->track_dca[i]);
			h1D_track_dcaxy  ->Fill(Reader->track_dcaxy[i]);
			h1D_track_nSigmaPion  ->Fill(Reader->track_nSigmaPion[i]);
			h1D_track_nSigmaKaon  ->Fill(Reader->track_nSigmaKaon[i]);
			h1D_track_nSigmaProton ->Fill(Reader->track_nSigmaProton[i]);
			h1D_track_ch ->Fill(Reader->track_ch[i]);
		}

	
}



void ntp_Lambda_Histogram::Fill_PairPlots(TLorentzVector *v1,TLorentzVector *v2, int pair_type){
	double delta_Rapidity = TMath::Abs( v1->Rapidity() - v2->Rapidity() );
	double delta_Phi = TMath::ACos( TMath::Cos( v1->Phi() - v2->Phi() ) );
	double delta_Pt  = TMath::Abs(v1->Pt() - v2->Pt() );
	double deltaR = TMath::Sqrt( delta_Phi * delta_Phi + delta_Rapidity * delta_Rapidity  );


	h2D_NLambda_PtDiff[pair_type]->Fill(Reader->NLambda,delta_Pt);
	h2D_NLambda_RapidityDiff[pair_type]->Fill(Reader->NLambda,delta_Rapidity);
	h2D_NLambda_PhiDiff[pair_type]->Fill(Reader->NLambda,delta_Phi);
	h2D_NLambda_DeltaR[pair_type]->Fill(Reader->NLambda,deltaR);

	double Eta_max = v1->Eta();
	double Eta_min = v2->Eta();
	double Phi_max = v1->Phi();
	double Phi_min = v2->Phi();
	if(Eta_min > Eta_max ){
		Eta_max = v2->Eta();
		Eta_min = v1->Eta();
	}

	if(Phi_min > Phi_max ){
		Phi_max =  v2->Phi();
		Phi_min =  v1->Phi();
	}


	double Window_Eta_max = Eta_max; 
	double Window_Eta_min = Eta_min;
	double delta_Eta = Eta_max - Eta_min;

	double Window1_Phi_max = Phi_max;
	double Window1_Phi_min = Phi_min;

	double Window2_Phi_max = Phi_max; 
	double Window2_Phi_min = Phi_min;

	if(TMath::Abs(Phi_max-Phi_min) > TMath::Pi() ){
		Window1_Phi_max = TMath::Pi();
		Window1_Phi_min = Phi_max;
		Window2_Phi_max = Phi_min; 
		Window2_Phi_min = -TMath::Pi();
	}

	int NTrks_InWindow = 0 ; 
	for(int i_trk = 0 ; i_trk < Reader->track_Number; i_trk++ ){
		 bool IsEtaIn  = (Reader->track_eta[i_trk] < Window_Eta_max) && (Reader->track_eta[i_trk] > Window_Eta_min)  ;
		 bool IsPhiIn1 = (Reader->track_phi[i_trk] < Window1_Phi_max)&& (Reader->track_phi[i_trk] > Window1_Phi_min) ;
		 bool IsPhiIn2 = (Reader->track_phi[i_trk] < Window2_Phi_max)&& (Reader->track_phi[i_trk] > Window2_Phi_min) ;
		 bool IsPhiIn = IsPhiIn1 || IsPhiIn2;
		 if ( IsEtaIn && IsPhiIn  ) NTrks_InWindow ++;
	}



	h2D_DeltaR_NTrksInWindow[pair_type]->Fill( TMath::Sqrt( delta_Phi * delta_Phi + delta_Eta * delta_Eta  )  , NTrks_InWindow  );       



}



void ntp_Lambda_Histogram::Fill_Mass2D(int i_lambda,int j_lambda){
	int pti_bin = 0;
	if(Reader->pair_pt[i_lambda] > 1.5 ) pti_bin = 1;
	int ptj_bin = 0; 
	if(Reader->pair_pt[j_lambda] > 1.5 ) ptj_bin = 1;

	TLorentzVector Lambda_i;
	TLorentzVector Lambda_j;
	Lambda_i.SetPtEtaPhiM(Reader->pair_pt[i_lambda],Reader->pair_eta[i_lambda],Reader->pair_phi[i_lambda],Reader->pair_mass[i_lambda]);
	Lambda_j.SetPtEtaPhiM(Reader->pair_pt[j_lambda],Reader->pair_eta[j_lambda],Reader->pair_phi[j_lambda],Reader->pair_mass[j_lambda]);
	double delta_phi = TMath::ACos(TMath::Cos( Lambda_i.Phi()- Lambda_j.Phi() ) );
	double delta_rapidity = TMath::Abs( Lambda_i.Rapidity()- Lambda_j.Rapidity()  );
	double delta_R = TMath::Sqrt( delta_phi *delta_phi + delta_rapidity * delta_rapidity  );

	std::vector<int> Range_Type; Range_Type.clear();
	for(int i=0; i < Range_Bin; i ++){
		if(delta_R > Range_Low[i] && delta_R < Range_High[i] ){
			Range_Type.push_back(i);
		}
	}







	//US US
	if( Reader->pair_charge[i_lambda] == 0  && Reader->pair_charge[j_lambda] == 0 ){
			//L Lbar
			if( Reader->p1_ch[i_lambda] >0 &&  Reader->p1_ch[j_lambda] < 0 ) {
					h2D_Lambda_LambdaBar_US_US[pti_bin][ptj_bin]->Fill(Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda]);
					for(int ir = 0;ir < Range_Type.size();ir++) {h2D_Lambda_LambdaBar_US_US_DeltaR[Range_Type[ir]]->Fill( Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda] ); }
			}
			//Lbar L
			if( Reader->p1_ch[i_lambda] <0 &&  Reader->p1_ch[j_lambda] > 0 ) {
					h2D_Lambda_LambdaBar_US_US[ptj_bin][pti_bin]->Fill(Reader->pair_mass[j_lambda],Reader->pair_mass[i_lambda]);
					for(int ir = 0;ir < Range_Type.size();ir++) {h2D_Lambda_LambdaBar_US_US_DeltaR[Range_Type[ir]]->Fill( Reader->pair_mass[j_lambda],Reader->pair_mass[i_lambda] ); }
			}

			//L L
			if( Reader->p1_ch[i_lambda] >0 &&  Reader->p1_ch[j_lambda] > 0 ) {
					h2D_Lambda_Lambda_US_US[pti_bin][ptj_bin]->Fill(Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda]);
					for(int ir = 0;ir < Range_Type.size();ir++) {h2D_Lambda_Lambda_US_US_DeltaR[Range_Type[ir]]->Fill( Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda] ); }
			}

			//Lbar Lbar
			if( Reader->p1_ch[i_lambda] <0 &&  Reader->p1_ch[j_lambda] < 0 ) {
					h2D_LambdaBar_LambdaBar_US_US[pti_bin][ptj_bin]->Fill(Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda]);
					for(int ir = 0;ir < Range_Type.size();ir++) {h2D_LambdaBar_LambdaBar_US_US_DeltaR[Range_Type[ir]]->Fill( Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda] ); }
			}

	}

	// LS US
	if( Reader->pair_charge[i_lambda] == 1  && Reader->pair_charge[j_lambda] == 0 ){
			//L Lbar
			if( Reader->p1_ch[i_lambda] >0 &&  Reader->p1_ch[j_lambda] < 0 ) {
					h2D_Lambda_LambdaBar_US_LS[pti_bin][ptj_bin]->Fill(Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda]);
					for(int ir = 0;ir < Range_Type.size();ir++) {h2D_Lambda_LambdaBar_US_LS_DeltaR[Range_Type[ir]]->Fill( Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda] ); }
			}
			//Lbar L
			if( Reader->p1_ch[i_lambda] <0 &&  Reader->p1_ch[j_lambda] > 0 ) {
					h2D_Lambda_LambdaBar_US_LS[ptj_bin][pti_bin]->Fill(Reader->pair_mass[j_lambda],Reader->pair_mass[i_lambda]);
					for(int ir = 0;ir < Range_Type.size();ir++) {h2D_Lambda_LambdaBar_US_LS_DeltaR[Range_Type[ir]]->Fill( Reader->pair_mass[j_lambda],Reader->pair_mass[i_lambda] ); }
			}

			//L L
			if( Reader->p1_ch[i_lambda] >0 &&  Reader->p1_ch[j_lambda] > 0 ) {
					h2D_Lambda_Lambda_US_LS[pti_bin][ptj_bin]->Fill(Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda]);
					for(int ir = 0;ir < Range_Type.size();ir++) {h2D_Lambda_Lambda_US_LS_DeltaR[Range_Type[ir]]->Fill( Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda] ); }
			}

			//Lbar Lbar
			if( Reader->p1_ch[i_lambda] <0 &&  Reader->p1_ch[j_lambda] < 0 ) {
					h2D_LambdaBar_LambdaBar_US_LS[pti_bin][ptj_bin]->Fill(Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda]);
					for(int ir = 0;ir < Range_Type.size();ir++) {h2D_LambdaBar_LambdaBar_US_LS_DeltaR[Range_Type[ir]]->Fill( Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda] ); }
			}

	}
	
	// US LS
	if( Reader->pair_charge[i_lambda] == 0  && Reader->pair_charge[j_lambda] == 1 ){
			//L Lbar
			if( Reader->p1_ch[i_lambda] >0 &&  Reader->p1_ch[j_lambda] < 0 ) {
					h2D_Lambda_LambdaBar_US_LS[pti_bin][ptj_bin]->Fill(Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda]);
					for(int ir = 0;ir < Range_Type.size();ir++) {h2D_Lambda_LambdaBar_US_LS_DeltaR[Range_Type[ir]]->Fill( Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda] ); }
			}
			//Lbar L
			if( Reader->p1_ch[i_lambda] <0 &&  Reader->p1_ch[j_lambda] > 0 ) {
					h2D_Lambda_LambdaBar_US_LS[ptj_bin][pti_bin]->Fill(Reader->pair_mass[j_lambda],Reader->pair_mass[i_lambda]);
					for(int ir = 0;ir < Range_Type.size();ir++) {h2D_Lambda_LambdaBar_US_LS_DeltaR[Range_Type[ir]]->Fill( Reader->pair_mass[j_lambda],Reader->pair_mass[i_lambda] ); }
			}

			//L L
			if( Reader->p1_ch[i_lambda] >0 &&  Reader->p1_ch[j_lambda] > 0 ) {
					h2D_Lambda_Lambda_US_LS[pti_bin][ptj_bin]->Fill(Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda]);
					for(int ir = 0;ir < Range_Type.size();ir++) {h2D_Lambda_Lambda_US_LS_DeltaR[Range_Type[ir]]->Fill( Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda] ); }
			}	

			//Lbar Lbar
			if( Reader->p1_ch[i_lambda] <0 &&  Reader->p1_ch[j_lambda] < 0 ) {
					h2D_LambdaBar_LambdaBar_US_LS[pti_bin][ptj_bin]->Fill(Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda]);
					for(int ir = 0;ir < Range_Type.size();ir++) {h2D_LambdaBar_LambdaBar_US_LS_DeltaR[Range_Type[ir]]->Fill( Reader->pair_mass[i_lambda],Reader->pair_mass[j_lambda] ); }
			}

	}

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
	h1D_p1_Dcaxy    	->Reset("ICES");
	h1D_p1_nSigmaProton ->Reset("ICES");

	h1D_p2_Pt     		->Reset("ICES");
	h1D_p2_Eta    		->Reset("ICES");
	h1D_p2_Phi    		->Reset("ICES");
	h1D_p2_Dca    		->Reset("ICES");
	h1D_p2_Dcaxy    	->Reset("ICES");
	h1D_p2_nSigmaPion ->Reset("ICES");

	h1D_p1_plus_pt  ->Reset("ICES");
	h1D_p1_minus_pt ->Reset("ICES");
	h1D_p2_plus_pt  ->Reset("ICES");
	h1D_p2_minus_pt ->Reset("ICES");


	h2D_NLambda_NGoodLambda ->Reset("ICES");
	for(int i =0 ; i <3 ; i++){
		h2D_NLambda_PtDiff[i]->Reset("ICES");
		h2D_NLambda_RapidityDiff[i]->Reset("ICES");
		h2D_NLambda_PhiDiff[i]->Reset("ICES");
		h2D_NLambda_DeltaR[i]->Reset("ICES");
		h2D_DeltaR_NTrksInWindow[i]  ->Reset("ICES");
	}
	
	for(int i=0 ;i <2 ;i++){
		h2D_NLambda_pairMass[i]->Reset("ICES");
		h2D_pairPt_pairMass[i]  ->Reset("ICES");
		h2D_pairEta_pairMass[i] ->Reset("ICES");
		h2D_pairPhi_pairMass[i] ->Reset("ICES");
		h2D_pairDecayL_pairMass[i]->Reset("ICES");
		h2D_p1Pt_pairMass[i]->Reset("ICES");
		h2D_p2Pt_pairMass[i]->Reset("ICES");


	}


	h1D_track_Number ->Reset("ICES");
	h1D_track_pt     ->Reset("ICES");
	h1D_track_eta	 ->Reset("ICES");
	h1D_track_phi	 ->Reset("ICES");
	h1D_track_dca    ->Reset("ICES");
	h1D_track_dcaxy  ->Reset("ICES");
	h1D_track_nSigmaPion  ->Reset("ICES");
	h1D_track_nSigmaKaon  ->Reset("ICES");
	h1D_track_nSigmaProton ->Reset("ICES");
	h1D_track_ch ->Reset("ICES");

	for(int i = 0 ;i < 2 ; i++ ){
		for(int j=0; j <2 ;j++){
			h2D_Lambda_LambdaBar_US_US[i][j] ->Reset("ICES");
			h2D_Lambda_LambdaBar_US_LS[i][j] ->Reset("ICES");
			h2D_Lambda_Lambda_US_US[i][j]   ->Reset("ICES");
			h2D_Lambda_Lambda_US_LS[i][j]   ->Reset("ICES");
			h2D_LambdaBar_LambdaBar_US_US[i][j] ->Reset("ICES");
			h2D_LambdaBar_LambdaBar_US_LS[i][j] ->Reset("ICES");
		}
	}


	for(int i= 0 ;i < Range_Bin;i++){
		h2D_Lambda_LambdaBar_US_US_DeltaR[i] ->Reset("ICES");
		h2D_Lambda_LambdaBar_US_LS_DeltaR[i] ->Reset("ICES");
		h2D_Lambda_Lambda_US_US_DeltaR[i]    ->Reset("ICES");
		h2D_Lambda_Lambda_US_LS_DeltaR[i]    ->Reset("ICES");
		h2D_LambdaBar_LambdaBar_US_US_DeltaR[i] ->Reset("ICES");
		h2D_LambdaBar_LambdaBar_US_LS_DeltaR[i] ->Reset("ICES");
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
	h1D_p1_Dcaxy    	->Write();
	h1D_p1_nSigmaProton ->Write();

	h1D_p2_Pt     		->Write();
	h1D_p2_Eta    		->Write();
	h1D_p2_Phi    		->Write();
	h1D_p2_Dca    		->Write();
	h1D_p2_Dcaxy    	->Write();
	h1D_p2_nSigmaPion ->Write();

	h1D_p1_plus_pt  ->Write();
	h1D_p1_minus_pt ->Write();
	h1D_p2_plus_pt  ->Write();
	h1D_p2_minus_pt ->Write();

	h2D_NLambda_NGoodLambda->Write(); 
	for(int i =0 ; i <3 ; i++){
		h2D_NLambda_PtDiff[i]->Write();
		h2D_NLambda_RapidityDiff[i]->Write();
		h2D_NLambda_PhiDiff[i]->Write();
		h2D_NLambda_DeltaR[i]->Write();
		h2D_DeltaR_NTrksInWindow[i]  ->Write();
	}
	
	for(int i=0 ;i <2 ;i++){
		h2D_NLambda_pairMass[i]->Write();
		h2D_pairPt_pairMass[i] ->Write();
		h2D_pairEta_pairMass[i]->Write();
		h2D_pairPhi_pairMass[i]->Write();
		h2D_pairDecayL_pairMass[i]->Write();
		h2D_p1Pt_pairMass[i]->Write();
		h2D_p2Pt_pairMass[i]->Write();
		h2D_p1Pt_p2Pt[i]    ->Write();
	}


	h1D_track_Number ->Write();
	h1D_track_pt     ->Write();
	h1D_track_eta	 ->Write();
	h1D_track_phi	 ->Write();
	h1D_track_dca    ->Write();
	h1D_track_dcaxy  ->Write();
	h1D_track_nSigmaPion  ->Write();
	h1D_track_nSigmaKaon  ->Write();
	h1D_track_nSigmaProton ->Write();
	h1D_track_ch ->Write();




	for(int i = 0 ;i < 2 ; i++ ){
		for(int j=0; j <2 ;j++){
			h2D_Lambda_LambdaBar_US_US[i][j] ->Write();
			h2D_Lambda_LambdaBar_US_LS[i][j] ->Write();
			h2D_Lambda_Lambda_US_US[i][j]   ->Write();
			h2D_Lambda_Lambda_US_LS[i][j]  ->Write();
			h2D_LambdaBar_LambdaBar_US_US[i][j] ->Write();
			h2D_LambdaBar_LambdaBar_US_LS[i][j] ->Write();
		}
	}



	for(int i= 0 ;i < Range_Bin;i++){
		h2D_Lambda_LambdaBar_US_US_DeltaR[i] ->Write();
		h2D_Lambda_LambdaBar_US_LS_DeltaR[i] ->Write();
		h2D_Lambda_Lambda_US_US_DeltaR[i]    ->Write();
		h2D_Lambda_Lambda_US_LS_DeltaR[i]    ->Write();
		h2D_LambdaBar_LambdaBar_US_US_DeltaR[i] ->Write();
		h2D_LambdaBar_LambdaBar_US_LS_DeltaR[i] ->Write();
	}



	fout->Close();
	delete fout;
	
	
	
	

}






#endif 
