#ifndef ntp_Lambda_Analyzer_h 
#define ntp_Lambda_Analyzer_h

//include the header files here 

#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TLorentzVector.h>
 
#include <vector>
#include <string>
#include <iostream>
#include <numeric>


#include "constants.h"
#include "ntp_Lambda_Histogram.h"
#include "ntp_Lambda_Reader_v3.h"
#include "ntp_Lambda_EventSelecter.h"
#include "ntp_Lambda_LambdaSelecter.h"


class ntp_Lambda_Analyzer{
public:
	ntp_Lambda_Reader *SameEvent_Reader;
	

	ntp_Lambda_EventSelecter *EventSelecter;
	ntp_Lambda_LambdaSelecter *LambdaSelecter;


	
	ntp_Lambda_Histogram  *Histogramer; 


	



	ntp_Lambda_Analyzer();
	ntp_Lambda_Analyzer(ntp_Lambda_Reader *reader1, ntp_Lambda_Histogram *histogram, ntp_Lambda_EventSelecter *eventSelecter, ntp_Lambda_LambdaSelecter *lambdaSelecter  );

	~ntp_Lambda_Analyzer();




	
	int Pair_Type_Classifier(int idx1, int idx2);
	int Range_Type_Classifier(TLorentzVector *v1, TLorentzVector *v2);



	std::vector<int> FindDauTrk(std::vector<int> GoodLambdaFlag );
	bool IsCleanLambda(std::vector<int> DauTrkID,int i_lambda);


	void Analysis_Pair(int i_lambda,int j_lambda);
	void Analysis_QAPlot();

	


};

ntp_Lambda_Analyzer::ntp_Lambda_Analyzer(){

}

ntp_Lambda_Analyzer::ntp_Lambda_Analyzer(ntp_Lambda_Reader *reader1, ntp_Lambda_Histogram *histogram, ntp_Lambda_EventSelecter *eventSelecter, ntp_Lambda_LambdaSelecter *lambdaSelecter )
: SameEvent_Reader(reader1),Histogramer(histogram), EventSelecter(eventSelecter), LambdaSelecter(lambdaSelecter)
{

}




ntp_Lambda_Analyzer::~ntp_Lambda_Analyzer(){

}





int ntp_Lambda_Analyzer::Pair_Type_Classifier(int idx1, int idx2){
	//pair type 
	//1: Lambda Lambda_bar           -1:Lambda_bar 
	//2: Lambda Lambda 			
	//3: Lambda_bar Lambda_bar 		 
	//4: Lambda LS 					 -4:LS Lambda
	//5: Lambda_bar LS 				 -5:LS Lambda_bar
	//6: LS LS 


	//1: Lambda Lambda_bar 
	if(SameEvent_Reader->pair_charge[idx1] == 0 && SameEvent_Reader->pair_charge[idx2] == 0 && SameEvent_Reader->p1_ch[idx1] == 1 && SameEvent_Reader->p1_ch[idx2] == -1 ) return  1 ;
	//-1:Lambda_bar 
	if(SameEvent_Reader->pair_charge[idx1] == 0 && SameEvent_Reader->pair_charge[idx2] == 0 && SameEvent_Reader->p1_ch[idx1] ==-1 && SameEvent_Reader->p1_ch[idx2] ==  1 ) return -1 ;
	//2: Lambda Lambda 	
	if(SameEvent_Reader->pair_charge[idx1] == 0 && SameEvent_Reader->pair_charge[idx2] == 0 && SameEvent_Reader->p1_ch[idx1] == 1 && SameEvent_Reader->p1_ch[idx2] ==  1 ) return  2 ;
	//3: Lambda_bar Lambda_bar 		
	if(SameEvent_Reader->pair_charge[idx1] == 0 && SameEvent_Reader->pair_charge[idx2] == 0 && SameEvent_Reader->p1_ch[idx1] ==-1 && SameEvent_Reader->p1_ch[idx2] == -1 ) return  3 ;
	//4: Lambda LS 	
	if(SameEvent_Reader->pair_charge[idx1] == 0 && SameEvent_Reader->pair_charge[idx2] == 1 && SameEvent_Reader->p1_ch[idx1] == 1  ) return  4 ;
	//-4:LS Lambda
	if(SameEvent_Reader->pair_charge[idx1] == 1 && SameEvent_Reader->pair_charge[idx2] == 0 && SameEvent_Reader->p1_ch[idx2] == 1  ) return -4 ;
	//5: Lambda_bar LS
	if(SameEvent_Reader->pair_charge[idx1] == 0 && SameEvent_Reader->pair_charge[idx2] == 1 && SameEvent_Reader->p1_ch[idx1] == -1 ) return  5 ;
	//-5:LS Lambda_bar
	if(SameEvent_Reader->pair_charge[idx1] == 1 && SameEvent_Reader->pair_charge[idx2] == 0 && SameEvent_Reader->p1_ch[idx2] == -1 ) return -5 ;
	//6:LS Lambda_bar
	if(SameEvent_Reader->pair_charge[idx1] == 1 && SameEvent_Reader->pair_charge[idx2] == 1) return 6 ;
	return 0;
	

}

int ntp_Lambda_Analyzer::Range_Type_Classifier(TLorentzVector *v1, TLorentzVector *v2){
	double delta_phi 		= TMath::ACos(TMath::Cos( v1->Phi()-v2->Phi() ) );
	double delta_rapidity 	= TMath::Abs( v1->Rapidity() - v2->Rapidity()   );

	//range_Type 
	//0 : short range 
	//1 : long  range 
	if(delta_phi < TMath::Pi()/3. && delta_rapidity < 0.5 ) return 0;
	if(delta_phi > TMath::Pi()/3. || delta_rapidity > 0.5 ) return 1; 
	return -1;  

}





void ntp_Lambda_Analyzer::Analysis_Pair(int i_lambda,int j_lambda){
	if( SameEvent_Reader->p1_InEventID[i_lambda] == SameEvent_Reader->p1_InEventID[j_lambda] || 
	   		SameEvent_Reader->p1_InEventID[i_lambda] == SameEvent_Reader->p2_InEventID[i_lambda] || 
	   		SameEvent_Reader->p1_InEventID[i_lambda] == SameEvent_Reader->p2_InEventID[j_lambda] || 
	   		SameEvent_Reader->p1_InEventID[j_lambda] == SameEvent_Reader->p2_InEventID[i_lambda] || 
	   		SameEvent_Reader->p1_InEventID[j_lambda] == SameEvent_Reader->p2_InEventID[j_lambda] ||
	   		SameEvent_Reader->p2_InEventID[i_lambda] == SameEvent_Reader->p2_InEventID[j_lambda] ) return ;
				
			

		//---------------------------Pair Type Classification-------------------------------
		int Pair_Type = 0 ; 
		int id_Lambda1= i_lambda ; 
		int id_Lambda2= j_lambda ;


		Pair_Type = Pair_Type_Classifier(i_lambda,j_lambda);

		if(Pair_Type == 1){
			id_Lambda1 = i_lambda;id_Lambda2 = j_lambda;
		}

		else if(Pair_Type == -1){
			id_Lambda1 = j_lambda;id_Lambda2 = i_lambda;
		}

		else if(Pair_Type == 2){
			id_Lambda1 = i_lambda;id_Lambda2 = j_lambda;
		}
		else if(Pair_Type == 3){
			id_Lambda1 = i_lambda;id_Lambda2 = j_lambda;
		}
		else{
			
			std::cout<<"Something went wrong with the pair type classifier"<<std::endl;
			return ;
		}
		TLorentzVector Lambda1; Lambda1.SetPtEtaPhiM( SameEvent_Reader->pair_pt[id_Lambda1], SameEvent_Reader->pair_eta[id_Lambda1], SameEvent_Reader->pair_phi[id_Lambda1], SameEvent_Reader->pair_mass[id_Lambda1]  );
		TLorentzVector Lambda2; Lambda2.SetPtEtaPhiM( SameEvent_Reader->pair_pt[id_Lambda2], SameEvent_Reader->pair_eta[id_Lambda2], SameEvent_Reader->pair_phi[id_Lambda2], SameEvent_Reader->pair_mass[id_Lambda2]  );


		Histogramer->Fill_PairPlots(&Lambda1,&Lambda2,TMath::Abs(Pair_Type)-1);




};



std::vector<int> ntp_Lambda_Analyzer::FindDauTrk(std::vector<int> GoodLambdaFlag ){

	std::vector<int> DauTrkID; 
	DauTrkID.clear();
	for(int i_lambda=0;i_lambda < GoodLambdaFlag.size();i_lambda++){
			if(GoodLambdaFlag[i_lambda]==0) continue;
			bool p1Flag =false;
			for(int idau1=0;idau1<DauTrkID.size();idau1++){
					if( SameEvent_Reader->p1_InEventID[i_lambda] == DauTrkID[idau1] ) p1Flag == true;
			}
			if(p1Flag==false) DauTrkID.push_back(SameEvent_Reader->p1_InEventID[i_lambda]);

	}

	for(int i_lambda=0;i_lambda < GoodLambdaFlag.size();i_lambda++){
			if(GoodLambdaFlag[i_lambda]==0) continue;
			bool p2Flag =false;
			for(int idau2=0;idau2<DauTrkID.size();idau2++){
					if( SameEvent_Reader->p2_InEventID[i_lambda] == DauTrkID[idau2] ) p2Flag == true;
			}
			if(p2Flag==false) DauTrkID.push_back(SameEvent_Reader->p2_InEventID[i_lambda]);

	}


	return DauTrkID;

}



bool ntp_Lambda_Analyzer::IsCleanLambda(std::vector<int> DauTrkID,int i_lambda){
		
	int NTrkAround = 0 ;

	for(int iTrk = 0; iTrk < SameEvent_Reader->track_Number;iTrk++){
		bool IsDauTrk = false;
		for(int iDauTrk=0; iDauTrk<DauTrkID.size();iDauTrk++){
			if(DauTrkID[iDauTrk] == SameEvent_Reader->track_InEventID[iTrk]){
				IsDauTrk = true;
				break;
			}
		}
		if(IsDauTrk) continue;


		double deltaEta = TMath::Abs( SameEvent_Reader->pair_eta[i_lambda] - SameEvent_Reader->track_eta[iTrk] );
		double deltaPhi = TMath::ACos( TMath::Cos( SameEvent_Reader->pair_phi[i_lambda] - SameEvent_Reader->track_phi[iTrk] )   );
		double deltaR = TMath::Sqrt( deltaEta*deltaEta + deltaPhi * deltaPhi );
		if(deltaR < CleanRadius  && SameEvent_Reader->track_dca[iTrk] < 1 && SameEvent_Reader->track_pt[iTrk] <0.6  ) NTrkAround++;

	}
	Histogramer->h1D_NTrkAround->Fill(NTrkAround);
	if(NTrkAround > 0 ) return false;
	else return true;


}



void ntp_Lambda_Analyzer::Analysis_QAPlot(){

	
	unsigned long N_Inputfiles_SE = SameEvent_Reader->InputFiles.size();

	//-------------------------------Enter i_file loop---------------------------------
	for(unsigned long i_file = 0 ; i_file < N_Inputfiles_SE ; i_file ++){
		//Open the file 
		if(i_file%10==0) std::cout<<"i_file="<<i_file<<std::endl;
		TFile *fin=TFile::Open( SameEvent_Reader->InputFiles[i_file].c_str() ,"READ");
		if(fin==0){
			std::cout<<"Can not open the file:"<< SameEvent_Reader->InputFiles[i_file] <<", Skip this" << std::endl;
			continue;
		}
		TTree *tmp_tree = (TTree *)fin->Get("ntp_Lambda");
		if(tmp_tree==0){
			std::cout<<"Can not get the tree, skip this file."<<std::endl;
			continue;
		}

		SameEvent_Reader->Init(tmp_tree);
		//Get the number of entries in current tree
		Long64_t N_Events=SameEvent_Reader->fChain->GetEntries();
		

		//---------------------------Enter i_event loop----------------------------
		for(Long64_t i_event=0; i_event < N_Events ; i_event++ ){
			SameEvent_Reader->fChain->GetEntry(i_event);
			//select on events Trig 
			std::vector<int> TriggerIDList;TriggerIDList.clear();
			for(int iTrig = 0; iTrig < SameEvent_Reader->mNTrigs;iTrig++){
				TriggerIDList.push_back( SameEvent_Reader->mTrigId[iTrig]);
			}
			
			//Fill Histograms of QA plot (without any cut);
			Histogramer->Fill_QAplots();

			//------------------------Make some selections on the events-----------------------------
			if( !EventSelecter->IsGoodEvent(TriggerIDList) ) continue;
			for(int i_Xi =0 ; i_Xi < SameEvent_Reader->NXi;i_Xi++){
				if(SameEvent_Reader->Xi_Charge[i_Xi] ==0 ) continue;
				if(SameEvent_Reader->Xi_DCAdaughters[i_Xi] >2 ) continue;
				if(SameEvent_Reader->Xi_DecayL[i_Xi] <2 ) continue;
				if(SameEvent_Reader->Xi_DCA[i_Xi] > 2 ) continue;
				if(SameEvent_Reader->DauLambda_mass[i_Xi] < 1.113) continue;
				if(SameEvent_Reader->DauLambda_mass[i_Xi] > 1.119) continue;
				//if( TMath::Cos( SameEvent_Reader->Xi_theta[i_Xi] ) < 0.9 ) continue;
				if( SameEvent_Reader->pion3_InEventID[i_Xi] == SameEvent_Reader->DauLambda_Dau1_InEventID[i_Xi] ) continue;
				if( SameEvent_Reader->pion3_InEventID[i_Xi] == SameEvent_Reader->DauLambda_Dau2_InEventID[i_Xi] ) continue;
				TLorentzVector DauLam; 
				TLorentzVector DauPion;
				DauLam.SetPtEtaPhiM(SameEvent_Reader->DauLambda_pt[i_Xi], SameEvent_Reader->DauLambda_eta[i_Xi],SameEvent_Reader->DauLambda_phi[i_Xi],SameEvent_Reader->DauLambda_mass[i_Xi]);
				DauPion.SetPtEtaPhiM(SameEvent_Reader->pion3_pt[i_Xi],SameEvent_Reader->pion3_eta[i_Xi],SameEvent_Reader->pion3_phi[i_Xi],MASS_PION);
				TLorentzVector Xi_ReCal= DauLam + DauPion;
				Histogramer->h1D_XiMass->Fill(SameEvent_Reader->Xi_mass[i_Xi]);
				Histogramer->h1D_XiMass_ReCal->Fill(Xi_ReCal.M());
				//std::cout<<"Xi_Mass:"<<SameEvent_Reader->Xi_mass[i_Xi]<<std::endl;
				//std::cout<<"Xi_Mass_ReCal:"<<Xi_ReCal.M()<<std::endl;
			}
			
							
		}
		//---------------------------End i_event loop----------------------------
		fin->Close();
		delete fin;
	}

	//-------------------------------Enter i_file loop---------------------------------

}





#endif
