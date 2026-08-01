#ifndef ntp_Lambda_Analyzer_h 
#define ntp_Lambda_Analyzer_h

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
#include "ntp_Lambda_Histogram.h"
#include "ntp_Lambda_Reader.h"
#include "ntp_Lambda_EventSelecter.h"
#include "ntp_Lambda_LambdaSelecter.h"


class ntp_Lambda_Analyzer{
public:
	ntp_Lambda_Reader *SameEvent_Reader;
	

	ntp_Lambda_EventSelecter *EventSelecter;
	ntp_Lambda_LambdaSelecter *LambdaSelecter;


	
	ntp_Lambda_Histogram  *Histogramer; 



	double Cali_scale_max ;
	double Cali_scale_min ;
	int Cali_NPoint    ;
	std::vector<double> Cali_scale;





	ntp_Lambda_Analyzer();
	ntp_Lambda_Analyzer(ntp_Lambda_Reader *reader1, ntp_Lambda_Histogram *histogram, ntp_Lambda_EventSelecter *eventSelecter, ntp_Lambda_LambdaSelecter *lambdaSelecter,double max, double min , int n  );

	~ntp_Lambda_Analyzer();
	
	int Pair_Type_Classifier(int idx1, int idx2);
	void Analysis_Cali();

	


};

ntp_Lambda_Analyzer::ntp_Lambda_Analyzer(){
	

}

ntp_Lambda_Analyzer::ntp_Lambda_Analyzer(ntp_Lambda_Reader *reader1, ntp_Lambda_Histogram *histogram, ntp_Lambda_EventSelecter *eventSelecter, ntp_Lambda_LambdaSelecter *lambdaSelecter,double max, double min , int n )
: SameEvent_Reader(reader1),Histogramer(histogram), EventSelecter(eventSelecter), LambdaSelecter(lambdaSelecter),Cali_scale_max(max),Cali_scale_min(min),Cali_NPoint(n)
{
	double delta_Cali_scale = (Cali_scale_max - Cali_scale_min)/10.;
	Cali_scale.clear();
	for(int i =0 ; i < (Cali_NPoint +1) ;i ++){
		Cali_scale.push_back( Cali_scale_min + i * delta_Cali_scale  );
	}


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











void ntp_Lambda_Analyzer::Analysis_Cali(){

	
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
			if( !EventSelecter->IsGoodEvent(TriggerIDList) ) continue;
			Histogramer->Fill_EventInfo();

			//------------------------Make some selections on the events-----------------------------
			

			//------------------------Enter Loop of i_Lambda--------------------------------------
			for(int i_Lambda =0; i_Lambda<SameEvent_Reader->NLambda;i_Lambda++){
				TLorentzVector proton_orign; proton_orign.SetPtEtaPhiM(SameEvent_Reader->p1_pt[i_Lambda],SameEvent_Reader->p1_eta[i_Lambda],SameEvent_Reader->p1_phi[i_Lambda],MASS_PROTON);
				TLorentzVector pion_orign;   pion_orign.SetPtEtaPhiM(SameEvent_Reader->p2_pt[i_Lambda],SameEvent_Reader->p2_eta[i_Lambda],SameEvent_Reader->p2_phi[i_Lambda],MASS_PION);
				TLorentzVector Lambda_origin;  Lambda_origin.SetPtEtaPhiM(SameEvent_Reader->pair_pt[i_Lambda],SameEvent_Reader->pair_eta[i_Lambda],SameEvent_Reader->pair_phi[i_Lambda],SameEvent_Reader->pair_mass[i_Lambda]);
				std::vector<int> GoodLambdaFlag;GoodLambdaFlag.clear();
				//if(SameEvent_Reader->p1_ch[i_Lambda] < 0  )  continue; // select Lambda 
				//if(SameEvent_Reader->p1_ch[i_Lambda] > 0  )  continue; // select LambdaBar 

				//---------------------Enter Loop of i_scale----------------------------------
				for(int i_scale = 0 ; i_scale < Cali_scale.size();i_scale++){
					// scale the momentum
					TLorentzVector proton_scaled; proton_scaled.SetXYZM(proton_orign.X()*Cali_scale[i_scale], proton_orign.Y()*Cali_scale[i_scale], proton_orign.Z()*Cali_scale[i_scale],MASS_PROTON );
					TLorentzVector pion_scaled;   pion_scaled.SetXYZM(pion_orign.X()*Cali_scale[i_scale], pion_orign.Y()*Cali_scale[i_scale], pion_orign.Z()*Cali_scale[i_scale],MASS_PION );
					TLorentzVector Lambda_scaled = proton_scaled + pion_scaled;
					// check if it is good Lambda
					int isGoodLambda = ( 
									LambdaSelecter->IsGoodLambda(		pion_scaled.Pt() , proton_scaled.Pt(),
																pion_scaled.Eta(), proton_scaled.Eta(),
																Lambda_scaled.Pt()   , Lambda_scaled.Rapidity(),
																Lambda_scaled.M()    , SameEvent_Reader->pair_decayL[i_Lambda],
																SameEvent_Reader->pair_theta[i_Lambda],SameEvent_Reader->pair_DCAdaughters[i_Lambda])
				 				&& LambdaSelecter->IsGoodLambdaCharge(SameEvent_Reader->pair_charge[i_Lambda]) 
				 				&& LambdaSelecter->IsGoodLambdaDCA(SameEvent_Reader->pair_decayL[i_Lambda], SameEvent_Reader->pair_theta[i_Lambda] )
				 				&& LambdaSelecter->IsGoodDauDCA(SameEvent_Reader->p1_dca[i_Lambda], SameEvent_Reader->p2_dca[i_Lambda] )
				 				   );
					GoodLambdaFlag.push_back(isGoodLambda);
					if (isGoodLambda ==0 ) continue;
					Histogramer->Fill_LambdaInfo(i_scale,Lambda_scaled, SameEvent_Reader->pair_decayL[i_Lambda] );
					Histogramer->Fill_DauInfo(i_scale,Lambda_scaled,proton_scaled,pion_scaled);

				}
				//---------------------End Loop of i_scale----------------------------------
				int NGoodLambda = std::accumulate(GoodLambdaFlag.begin(), GoodLambdaFlag.end(), 0);
				if(NGoodLambda > 0 ) {
					Histogramer->Fill_LambdaInfo(SameEvent_Reader->pair_charge[i_Lambda],SameEvent_Reader->pair_DCAdaughters[i_Lambda],SameEvent_Reader->pair_theta[i_Lambda],SameEvent_Reader->pair_decayL[i_Lambda]);
					Histogramer->Fill_DauInfo(SameEvent_Reader->p1_eta[i_Lambda],SameEvent_Reader->p1_phi[i_Lambda],SameEvent_Reader->p1_dca[i_Lambda],SameEvent_Reader->p1_dcaxy[i_Lambda],SameEvent_Reader->p1_nSigmaProton[i_Lambda],
											  SameEvent_Reader->p2_eta[i_Lambda],SameEvent_Reader->p2_phi[i_Lambda],SameEvent_Reader->p2_dca[i_Lambda],SameEvent_Reader->p2_dcaxy[i_Lambda],SameEvent_Reader->p2_nSigmaPion[i_Lambda]);
				}
			}
			//------------------------End Loop of i_Lambda--------------------------------------

			
			
			
			
					
		}
		//---------------------------End i_event loop----------------------------
		fin->Close();
		delete fin;
	}

	//-------------------------------Enter i_file loop---------------------------------

}





#endif
