#ifndef ntp_K0s_Analyzer_h 
#define ntp_K0s_Analyzer_h

//include the header files here 

#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TGraph.h>
#include <vector>
#include <string>
#include <iostream>
#include <numeric>


#include "constants.h"
#include "ntp_K0s_Histogram.h"
#include "ntp_K0s_Reader_v2.h"
#include "ntp_K0s_EventSelecter.h"
#include "ntp_K0s_K0sSelecter.h"


class ntp_K0s_Analyzer{
public:
	ntp_K0s_Reader *SameEvent_Reader;
	

	ntp_K0s_EventSelecter *EventSelecter;
	ntp_K0s_K0sSelecter *K0sSelecter;


	
	ntp_K0s_Histogram  *Histogramer; 



	double Cali_scale_max = 1.000;
	double Cali_scale_min = 0.995;
	int Cali_NPoint    = 10;
	std::vector<double> Cali_scale;





	ntp_K0s_Analyzer();
	ntp_K0s_Analyzer(ntp_K0s_Reader *reader1, ntp_K0s_Histogram *histogram, ntp_K0s_EventSelecter *eventSelecter, ntp_K0s_K0sSelecter *K0sSelecter,double max, double min , int n  );

	~ntp_K0s_Analyzer();
	
	int Pair_Type_Classifier(int idx1, int idx2);
	void Analysis_Cali();

	


};

ntp_K0s_Analyzer::ntp_K0s_Analyzer(){
	double delta_Cali_scale = (Cali_scale_max - Cali_scale_min)/10.;
	Cali_scale.clear();
	for(int i =0 ; i < (Cali_NPoint +1) ;i ++){
		Cali_scale.push_back( Cali_scale_min + i * delta_Cali_scale  );
	}

}

ntp_K0s_Analyzer::ntp_K0s_Analyzer(ntp_K0s_Reader *reader1, ntp_K0s_Histogram *histogram, ntp_K0s_EventSelecter *eventSelecter, ntp_K0s_K0sSelecter *K0sSelecter,double max, double min , int n )
: SameEvent_Reader(reader1),Histogramer(histogram), EventSelecter(eventSelecter), K0sSelecter(K0sSelecter),Cali_scale_max(max),Cali_scale_min(min),Cali_NPoint(n)
{
	double delta_Cali_scale = (Cali_scale_max - Cali_scale_min)/10.;
	Cali_scale.clear();
	for(int i =0 ; i < (Cali_NPoint +1) ;i ++){
		Cali_scale.push_back( Cali_scale_min + i * delta_Cali_scale  );
	}


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











void ntp_K0s_Analyzer::Analysis_Cali(){

	
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
			Histogramer->Fill_EventInfo();

			//------------------------Make some selections on the events-----------------------------
			

			//------------------------Enter Loop of i_K0s--------------------------------------
			for(int i_K0s =0; i_K0s<SameEvent_Reader->NK0s;i_K0s++){
				TLorentzVector pion1_orign; pion1_orign.SetPtEtaPhiM(SameEvent_Reader->p1_pt[i_K0s],SameEvent_Reader->p1_eta[i_K0s],SameEvent_Reader->p1_phi[i_K0s],MASS_PION);
				TLorentzVector pion2_orign; pion2_orign.SetPtEtaPhiM(SameEvent_Reader->p2_pt[i_K0s],SameEvent_Reader->p2_eta[i_K0s],SameEvent_Reader->p2_phi[i_K0s],MASS_PION);
				TLorentzVector K0s_origin;  K0s_origin.SetPtEtaPhiM(SameEvent_Reader->pair_pt[i_K0s],SameEvent_Reader->pair_eta[i_K0s],SameEvent_Reader->pair_phi[i_K0s],SameEvent_Reader->pair_mass[i_K0s]);
				std::vector<int> GoodK0sFlag;GoodK0sFlag.clear();
				//---------------------Enter Loop of i_scale----------------------------------
				for(int i_scale = 0 ; i_scale < Cali_scale.size();i_scale++){
					// scale the momentum
					TLorentzVector pion1_scaled; pion1_scaled.SetXYZM(pion1_orign.X()*Cali_scale[i_scale], pion1_orign.Y()*Cali_scale[i_scale], pion1_orign.Z()*Cali_scale[i_scale],MASS_PION );
					TLorentzVector pion2_scaled; pion2_scaled.SetXYZM(pion2_orign.X()*Cali_scale[i_scale], pion2_orign.Y()*Cali_scale[i_scale], pion2_orign.Z()*Cali_scale[i_scale],MASS_PION );
					TLorentzVector K0s_scaled = pion1_scaled + pion2_scaled;
					// check if it is good K0s
					int isGoodK0s = ( 
									K0sSelecter->IsGoodK0s(		pion2_scaled.Pt() , pion1_scaled.Pt(),
																pion2_scaled.Eta(), pion1_scaled.Eta(),
																K0s_scaled.Pt()   , K0s_scaled.Rapidity(),
																K0s_scaled.M()    , SameEvent_Reader->pair_decayL[i_K0s],
																SameEvent_Reader->pair_theta[i_K0s],SameEvent_Reader->pair_DCAdaughters[i_K0s])
				 				&& K0sSelecter->IsGoodK0sCharge(SameEvent_Reader->pair_charge[i_K0s]) 
				 				&& K0sSelecter->IsGoodK0sDCA(SameEvent_Reader->pair_decayL[i_K0s], SameEvent_Reader->pair_theta[i_K0s] )
				 				&& K0sSelecter->IsGoodDauDCA(SameEvent_Reader->p1_dca[i_K0s], SameEvent_Reader->p2_dca[i_K0s] )
				 				   );
					GoodK0sFlag.push_back(isGoodK0s);
					if (isGoodK0s ==0 ) continue;
					Histogramer->Fill_K0sInfo(i_scale,K0s_scaled, SameEvent_Reader->pair_decayL[i_K0s] );
					Histogramer->Fill_DauPionInfo(i_scale,K0s_scaled,pion1_scaled,pion2_scaled);

				}
				//---------------------End Loop of i_scale----------------------------------
				int NGoodK0s = std::accumulate(GoodK0sFlag.begin(), GoodK0sFlag.end(), 0);
				if(NGoodK0s > 0 ) {
					Histogramer->Fill_K0sInfo(SameEvent_Reader->pair_charge[i_K0s],SameEvent_Reader->pair_DCAdaughters[i_K0s],SameEvent_Reader->pair_theta[i_K0s],SameEvent_Reader->pair_decayL[i_K0s]);
					Histogramer->Fill_DauPionInfo(SameEvent_Reader->p1_eta[i_K0s],SameEvent_Reader->p1_phi[i_K0s],SameEvent_Reader->p1_dca[i_K0s],SameEvent_Reader->p1_dcaxy[i_K0s],SameEvent_Reader->p1_nSigmaPion[i_K0s]
												  SameEvent_Reader->p2_eta[i_K0s],SameEvent_Reader->p2_phi[i_K0s],SameEvent_Reader->p2_dca[i_K0s],SameEvent_Reader->p2_dcaxy[i_K0s],SameEvent_Reader->p2_nSigmaPion[i_K0s]);
				}
			}
			//------------------------End Loop of i_K0s--------------------------------------

			
			
			f
			
					
		}
		//---------------------------End i_event loop----------------------------
		fin->Close();
		delete fin;
	}

	//-------------------------------Enter i_file loop---------------------------------

}





#endif
