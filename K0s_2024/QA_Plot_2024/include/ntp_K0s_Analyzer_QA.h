#ifndef ntp_K0s_Analyzer_h 
#define ntp_K0s_Analyzer_h

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
#include "ntp_K0s_Histogram.h"
#include "ntp_K0s_Reader.h"
#include "ntp_K0s_EventSelecter.h"
#include "ntp_K0s_K0sSelecter.h"


class ntp_K0s_Analyzer{
public:
	ntp_K0s_Reader *SameEvent_Reader;
	

	ntp_K0s_EventSelecter *EventSelecter;
	ntp_K0s_K0sSelecter *K0sSelecter;


	
	ntp_K0s_Histogram  *Histogramer; 


	



	ntp_K0s_Analyzer();
	ntp_K0s_Analyzer(ntp_K0s_Reader *reader1, ntp_K0s_Histogram *histogram, ntp_K0s_EventSelecter *eventSelecter, ntp_K0s_K0sSelecter *K0sSelecter  );

	~ntp_K0s_Analyzer();
	
	int Pair_Type_Classifier(int idx1, int idx2);
	int Range_Type_Classifier(TLorentzVector *v1, TLorentzVector *v2);
	void Analysis_Pair(int i_K0s,int j_K0s);
	void Analysis_QAPlot();

	


};

ntp_K0s_Analyzer::ntp_K0s_Analyzer(){

}

ntp_K0s_Analyzer::ntp_K0s_Analyzer(ntp_K0s_Reader *reader1, ntp_K0s_Histogram *histogram, ntp_K0s_EventSelecter *eventSelecter, ntp_K0s_K0sSelecter *K0sSelecter )
: SameEvent_Reader(reader1),Histogramer(histogram), EventSelecter(eventSelecter), K0sSelecter(K0sSelecter)
{

}




ntp_K0s_Analyzer::~ntp_K0s_Analyzer(){

}





int ntp_K0s_Analyzer::Pair_Type_Classifier(int idx1, int idx2){
	//pair type 
	//1: K0s K0s          	 
	//2: K0s LS 					 -2:LS K0s
	//3: LS LS 


	//1: K0s K0s_bar 
	if(SameEvent_Reader->pair_charge[idx1] == 0 && SameEvent_Reader->pair_charge[idx2] == 0  ) return  1 ;
	//2: K0s LS	
	if(SameEvent_Reader->pair_charge[idx1] == 0 && SameEvent_Reader->pair_charge[idx2] == 1  ) return  2 ;
	//-2: LS  K0s 		
	if(SameEvent_Reader->pair_charge[idx1] == 1 && SameEvent_Reader->pair_charge[idx2] == 0  ) return  -2 ;
	//3: LS LS 	
	if(SameEvent_Reader->pair_charge[idx1] == 1 && SameEvent_Reader->pair_charge[idx2] == 1  ) return  3 ;
	return 0;
	

}

int ntp_K0s_Analyzer::Range_Type_Classifier(TLorentzVector *v1, TLorentzVector *v2){
	double delta_phi 		= TMath::ACos(TMath::Cos( v1->Phi()-v2->Phi() ) );
	double delta_rapidity 	= TMath::Abs( v1->Rapidity() - v2->Rapidity()   );

	//range_Type 
	//0 : short range 
	//1 : long  range 
	if(delta_phi < TMath::Pi()/3. && delta_rapidity < 0.5 ) return 0;
	if(delta_phi > TMath::Pi()/3. || delta_rapidity > 0.5 ) return 1; 
	return -1;  

}





void ntp_K0s_Analyzer::Analysis_Pair(int i_K0s,int j_K0s){
	if( SameEvent_Reader->p1_InEventID[i_K0s] == SameEvent_Reader->p1_InEventID[j_K0s] || 
	   		SameEvent_Reader->p1_InEventID[i_K0s] == SameEvent_Reader->p2_InEventID[i_K0s] || 
	   		SameEvent_Reader->p1_InEventID[i_K0s] == SameEvent_Reader->p2_InEventID[j_K0s] || 
	   		SameEvent_Reader->p1_InEventID[j_K0s] == SameEvent_Reader->p2_InEventID[i_K0s] || 
	   		SameEvent_Reader->p1_InEventID[j_K0s] == SameEvent_Reader->p2_InEventID[j_K0s] ||
	   		SameEvent_Reader->p2_InEventID[i_K0s] == SameEvent_Reader->p2_InEventID[j_K0s] ) return ;
				
			

		//---------------------------Pair Type Classification-------------------------------
		int Pair_Type = 0 ; 
		int id_K0s1= i_K0s ; 
		int id_K0s2= j_K0s ;


		Pair_Type = Pair_Type_Classifier(i_K0s,j_K0s);

		if(Pair_Type == 1){
			id_K0s1 = i_K0s;id_K0s2 = j_K0s;
		}
		else{
			
			std::cout<<"Something went wrong with the pair type classifier"<<std::endl;
			return ;
		}
		TLorentzVector K0s1; K0s1.SetPtEtaPhiM( SameEvent_Reader->pair_pt[id_K0s1], SameEvent_Reader->pair_eta[id_K0s1], SameEvent_Reader->pair_phi[id_K0s1], SameEvent_Reader->pair_mass[id_K0s1]  );
		TLorentzVector K0s2; K0s2.SetPtEtaPhiM( SameEvent_Reader->pair_pt[id_K0s2], SameEvent_Reader->pair_eta[id_K0s2], SameEvent_Reader->pair_phi[id_K0s2], SameEvent_Reader->pair_mass[id_K0s2]  );


		Histogramer->Fill_PairPlots(&K0s1,&K0s2,TMath::Abs(Pair_Type)-1);




};



void ntp_K0s_Analyzer::Analysis_QAPlot(){

	
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
		TTree *tmp_tree = (TTree *)fin->Get("ntp_K0s");
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
			if( !EventSelecter->IsGoodEvent(TriggerIDList) ) continue;


			//Fill Histograms of QA plot (without any cut);
			Histogramer->Fill_QAplots();

			//------------------------Make some selections on the events-----------------------------
			/*	
			std::vector<int> GoodK0sFlag;
			for(int i_K0s = 0; i_K0s<SameEvent_Reader->NK0s;i_K0s++){
				
				TLorentzVector v;
				v.SetPtEtaPhiM(SameEvent_Reader->pair_pt[i_K0s],SameEvent_Reader->pair_eta[i_K0s],SameEvent_Reader->pair_phi[i_K0s],SameEvent_Reader->pair_mass[i_K0s]);

				int isGoodK0s = ( 
									K0sSelecter->IsGoodK0s(SameEvent_Reader->p2_pt[i_K0s], SameEvent_Reader->p1_pt[i_K0s],
																SameEvent_Reader->p2_eta[i_K0s], SameEvent_Reader->p1_eta[i_K0s],
																SameEvent_Reader->pair_pt[i_K0s], v.Rapidity(),
																SameEvent_Reader->pair_mass[i_K0s], SameEvent_Reader->pair_decayL[i_K0s],
																SameEvent_Reader->pair_theta[i_K0s],SameEvent_Reader->pair_DCAdaughters[i_K0s])
				 				&& K0sSelecter->IsGoodK0sCharge(SameEvent_Reader->pair_charge[i_K0s]) 
				 				&& K0sSelecter->IsGoodK0sDCA(SameEvent_Reader->pair_decayL[i_K0s], SameEvent_Reader->pair_theta[i_K0s] )
				 				&& K0sSelecter->IsGoodDauDCA(SameEvent_Reader->p1_dca[i_K0s], SameEvent_Reader->p2_dca[i_K0s] )
				 				   );
				GoodK0sFlag.push_back(isGoodK0s);
			}
			//if(NGoodK0s < 2) continue;
			Histogramer->Fill_QAplots(GoodK0sFlag);
			int NGoodK0s = std::accumulate(GoodK0sFlag.begin(), GoodK0sFlag.end(), 0);
			Histogramer->Fill_NK0s_NGoodK0s(NGoodK0s);
			for(int i_K0s = 0 ; i_K0s < SameEvent_Reader->NK0s;i_K0s++){
				if(GoodK0sFlag[i_K0s]==0) continue;
				for(int j_K0s = i_K0s+1; j_K0s < SameEvent_Reader->NK0s;j_K0s++){
					if(GoodK0sFlag[j_K0s]==0) continue;
					Analysis_Pair(i_K0s,j_K0s);
				}
			}
			*/
			
					
		}
		//---------------------------End i_event loop----------------------------
		fin->Close();
		delete fin;
	}

	//-------------------------------Enter i_file loop---------------------------------

}





#endif
