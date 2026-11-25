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



	//3:0=LLbar, 1= LL, 2= LbarLbar  
	//2:L1 pt_bin
	//2:L2 pt_bin
	//2:L1 0 = US 1 = LS
	//2:L1 0 = US 1 = LS
	TH2D *h2D_L1L2Mass2D[3][Pt_Bin][Pt_Bin][2][2][Range_Bin];



	ntp_Lambda_Histogram();
	ntp_Lambda_Histogram(ntp_Lambda_Reader *reader,std::string outPutFile);
	void InitHitogram();
	void Fill_QAplots(std::vector<int> GoodLambdaFlag);
	
	int Find_PtBin(double Pt);
	int Find_IsUS(int charge);
	int Find_PairTypeBin(int proton1_ch,int proton2_ch);
	int Find_PairRangeBin(TLorentzVector Lambda_j, TLorentzVector Lambda_j);

	void Fill_Mass2D(int i_lambda,int j_lambda);

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

	for(int i1 = 0; i1 < 3; i1++){
		for(int i2 = 0; i2 <Pt_Bin; i2++){
			for(int i3 = 0; i3 <Pt_Bin; i3++){
				for(int i4 =0; i4 < 2; i4++){
					for(int i5=0; i5<2; i5++){
						for(int i6=0; i6 < Range_Bin; i6++){
							h2D_L1L2Mass2D[i1][i2][i3][i4][i5][i6] = new TH2D(Form("h2D_L1L2Mass2D_%d_%d_%d_%d_%d_%D",i1,i2,i3,i4,i5,i6),Form("h2D_L1L2Mass2D_%d_%d_%d_%d_%d_%D",i1,i2,i3,i4,i5,i6),,1000,1.07,1.20, 1000,1.07,1.20);
						}
					}
				}
			}
		}
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



int ntp_Lambda_Histogram::Find_PtBin(double Pt){
	int pt_bin =-1;
	for(i=0;i<Pt_Bin;i++){
		if(Pt > Pt_Low[i] && Pt < Pt_High[i]) pt_bin = i;
	}
	return pt_bin;
}

int ntp_Lambda_Histogram::Find_IsUS(int charge){
	if(charge==0) return 0;
	else return 1;
}

int ntp_Lambda_Histogram::Find_PairTypeBin(int proton1_ch,int proton2_ch){
	if(proton1_ch >0 && proton2_ch < 0 ) return 1;
	else if(proton1_ch <0 && proton2_ch > 0 ) return -1;
	else if(proton1_ch >0 && proton2_ch > 0 ) return 2;
	else if(proton1_ch <0 && proton2_ch < 0 ) return 3;

}

int ntp_Lambda_Histogram::Find_PairRangeBin(TLorentzVector Lambda_j, TLorentzVector Lambda_j){
	double delta_phi = TMath::ACos(TMath::Cos( Lambda_i.Phi()- Lambda_j.Phi() ) );
	double delta_rapidity = TMath::Abs( Lambda_i.Rapidity()- Lambda_j.Rapidity()  );
	double delta_R = TMath::Sqrt( delta_phi *delta_phi + delta_rapidity * delta_rapidity  );

	int range_bin=-1;
	for(int i=0; i < Range_Bin; i ++){
		if(delta_R > Range_Low[i] && delta_R < Range_High[i] ) range_bin = i;
	}
	return range_bin;

}


void ntp_Lambda_Histogram::Fill_Mass2D(int i_lambda, int j_lambda){
	int Li_PtBin = Find_PtBin(Reader->pair_pt[i_lambda]); 
	int Lj_PtBin = Find_PtBin(Reader->pair_pt[j_lambda]);
	
	int Li_IsUS  = Find_IsUS(Reader->pair_charge[i_lambda]);
	int Lj_IsUS  = Find_IsUS(Reader->pair_charge[j_lambda]);
	

	TLorentzVector lambda_i;
	TLorentzVector lambda_j;
	lambda_i.SetPtEtaPhiM(Reader->pair_pt[i_lambda],Reader->pair_eta[i_lambda],Reader->pair_phi[i_lambda],Reader->pair_mass[i_lambda]);
	lambda_j.SetPtEtaPhiM(Reader->pair_pt[j_lambda],Reader->pair_eta[j_lambda],Reader->pair_phi[j_lambda],Reader->pair_mass[j_lambda]);
	int PairType_Bin  = Find_PairTypeBin(Reader->p1_ch[i_lambda],Reader->p1_ch[j_lambda]);
	int PairRange_Bin = Find_PairRangeBin(lambda_j, lambda_j);


	double L1Mass = Reader->pair_mass[i_lambda] ; 
	double L2Mass = Reader->pair_mass[j_lambda] ;

	bool ShouldSwap = false;
	//some symmetrical cases 
	if( (PairType_Bin == 2 || PairType_Bin == 3) && (Li_IsUS == Lj_IsUS) ){
		double x = gRandom->Rndm();
		if(x > 0.5) ShouldSwap = true;
	}

	if( PairType_Bin == -1) ShouldSwap = true;

	if(ShouldSwap){
		int tmp_PtBin = Li_PtBin; Li_PtBin = Lj_PtBin; Lj_PtBin = tmp_PtBin;
		int tmp_IsUS  = Li_IsUS ; Li_IsUS  = Lj_IsUS ; Lj_IsUS  = tmp_IsUS;

		double tmp_Mass = L1Mass; L1Mass = L2Mass;L2Mass = L1Mass;
	}
	
	PairType_Bin = TMath::Abs(PairType_Bin)-1;
	h2D_L1L2Mass2D[PairType_Bin][Li_PtBin][Lj_PtBin][Li_IsUS][Lj_IsUS][PairRange_Bin]->Fill(L1Mass,L2Mass);

}











void ntp_Lambda_Histogram::Reset(){
	

	
	h1D_Vz         		->Reset("ICES");
	h1D_NLambda    		->Reset("ICES");
	h1D_TrigID     		->Reset("ICES");

	h2D_NLambda_Ntrks   ->Reset("ICES");

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

	for(int i1 = 0; i1 < 3; i1++){
		for(int i2 = 0; i2 <Pt_Bin; i2++){
			for(int i3 = 0; i3 <Pt_Bin; i3++){
				for(int i4 =0; i4 < 2; i4++){
					for(int i5=0; i5<2; i5++){
						for(int i6=0; i6 < Range_Bin; i6++){
							h2D_L1L2Mass2D[i1][i2][i3][i4][i5][i6] ->Reset("ICES");
						}
					}
				}
			}
		}
	}
	

	
}

void ntp_Lambda_Histogram::WriteAll(){
	TFile *fout= TFile::Open(OutPutFile.c_str(),"RECREATE");

	
	h1D_Vz         		->Write();
	h1D_NLambda    		->Write();
	h1D_TrigID     		->Write();


	h2D_NLambda_Ntrks   ->Write();

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


	for(int i1 = 0; i1 < 3; i1++){
		for(int i2 = 0; i2 <Pt_Bin; i2++){
			for(int i3 = 0; i3 <Pt_Bin; i3++){
				for(int i4 =0; i4 < 2; i4++){
					for(int i5=0; i5<2; i5++){
						for(int i6=0; i6 < Range_Bin; i6++){
							h2D_L1L2Mass2D[i1][i2][i3][i4][i5][i6] ->Write();
						}
					}
				}
			}
		}
	}

	fout->Close();
	delete fout;
	
	
	
	

}






#endif 
