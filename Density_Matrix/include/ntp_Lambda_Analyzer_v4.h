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
#include "ntp_Lambda_Calculator.h"
#include "ntp_Lambda_Histogram.h"
#include "ntp_Lambda_Reader.h"
#include "ntp_Lambda_MixTreeReader.h"
#include "ntp_Lambda_EventSelecter.h"
#include "ntp_Lambda_LambdaSelecter.h"


class ntp_Lambda_Analyzer{
public:
	ntp_Lambda_Reader *SameEvent_Reader;
	ntp_Lambda_Reader *MixEvent_Reader;
	ntp_Lambda_MixTreeReader *MixTreeReader;

	ntp_Lambda_EventSelecter *EventSelecter;
	ntp_Lambda_LambdaSelecter *LambdaSelecter;


	ntp_Lambda_Calculator *Calculator;
	ntp_Lambda_Histogram  *Histogramer; 


	//std::vector<bool> IsGoodLambda;
	std::vector<float> L_pair_pt;
	std::vector<float> L_pair_y;
	std::vector<float> L_pair_eta;
	std::vector<float> L_pair_phi;
	std::vector<float> L_pair_mass;
	std::vector<int>   L_pair_charge;
	
	

	std::vector<float> L_p1_pt;
	std::vector<float> L_p1_eta;
	std::vector<float> L_p1_phi;
	std::vector<float> L_p1_ch;

	std::vector<float> L_p2_pt;
	std::vector<float> L_p2_eta;
	std::vector<float> L_p2_phi;

	std::vector<float> Lbar_pair_pt;
	std::vector<float> Lbar_pair_y;
	std::vector<float> Lbar_pair_eta;
	std::vector<float> Lbar_pair_phi;
	std::vector<float> Lbar_pair_mass;
	std::vector<int>   Lbar_pair_charge;
	
	

	std::vector<float> Lbar_p1_pt;
	std::vector<float> Lbar_p1_eta;
	std::vector<float> Lbar_p1_phi;
	std::vector<float> Lbar_p1_ch;

	std::vector<float> Lbar_p2_pt;
	std::vector<float> Lbar_p2_eta;
	std::vector<float> Lbar_p2_phi;


	int MixEventPoolSize = 10000;
	int LLbar_USED= 0;



	ntp_Lambda_Analyzer();
	ntp_Lambda_Analyzer(ntp_Lambda_Reader *reader1, ntp_Lambda_Reader *reader2, ntp_Lambda_Calculator *calculator, ntp_Lambda_Histogram *hisogram, ntp_Lambda_MixTreeReader *mixtreeReader, ntp_Lambda_EventSelecter *eventSelecter, ntp_Lambda_LambdaSelecter *lambdaSelecter  );
	ntp_Lambda_Analyzer(ntp_Lambda_Reader *reader1, ntp_Lambda_Calculator *calculator, ntp_Lambda_Histogram *hisogram, ntp_Lambda_EventSelecter *eventSelecter, ntp_Lambda_LambdaSelecter *lambdaSelecter);

	~ntp_Lambda_Analyzer();
	
	void Fill_MixPool();
	int Pair_Type_Classifier(int idx1, int idx2);
	int Range_Type_Classifier(TLorentzVector *v1, TLorentzVector *v2);
	int Analyze_SEPair(int i_lambda,int j_lambda);
	void Analysis_SameEvent();
	void FindCounterparts(std::vector<TLorentzVector> *Lambda_counterpart,std::vector<TLorentzVector> *proton_counterpart,std::vector<TLorentzVector> *pion_counterpart,double rapidity,int I_LAMBDA);
	int Analyze_MEPair(int i_lambda,int j_lambda);
	void Analysis_MixEvent();


};

ntp_Lambda_Analyzer::ntp_Lambda_Analyzer(){

}

ntp_Lambda_Analyzer::ntp_Lambda_Analyzer(ntp_Lambda_Reader *reader1, ntp_Lambda_Reader *reader2, ntp_Lambda_Calculator *calculator, ntp_Lambda_Histogram *hisogram, ntp_Lambda_MixTreeReader *mixtreeReader, ntp_Lambda_EventSelecter *eventSelecter, ntp_Lambda_LambdaSelecter *lambdaSelecter )
: SameEvent_Reader(reader1),MixEvent_Reader(reader2),Calculator(calculator),Histogramer(hisogram), MixTreeReader(mixtreeReader), EventSelecter(eventSelecter), LambdaSelecter(lambdaSelecter)
{

}


ntp_Lambda_Analyzer::ntp_Lambda_Analyzer(ntp_Lambda_Reader *reader1, ntp_Lambda_Calculator *calculator, ntp_Lambda_Histogram *hisogram, ntp_Lambda_EventSelecter *eventSelecter, ntp_Lambda_LambdaSelecter *lambdaSelecter )
: SameEvent_Reader(reader1),MixEvent_Reader(0),Calculator(calculator),Histogramer(hisogram), EventSelecter(eventSelecter), LambdaSelecter(lambdaSelecter)
{

}

void ntp_Lambda_Analyzer::Fill_MixPool(){
	//IsGoodLambda.clear();
	L_pair_pt.clear();		Lbar_pair_pt.clear();
	L_pair_y.clear();   	Lbar_pair_y.clear();
	L_pair_eta.clear(); 	Lbar_pair_eta.clear();
	L_pair_phi.clear(); 	Lbar_pair_phi.clear();
	L_pair_mass.clear();	Lbar_pair_mass.clear();
	L_pair_charge.clear();	Lbar_pair_charge.clear();
	
	

	L_p1_pt.clear(); 		Lbar_p1_pt.clear();
	L_p1_eta.clear();		Lbar_p1_eta.clear();
	L_p1_phi.clear();		Lbar_p1_phi.clear();
	L_p1_ch.clear();		Lbar_p1_ch.clear();

	L_p2_pt.clear();		Lbar_p2_pt.clear();
	L_p2_eta.clear();		Lbar_p2_eta.clear();
	L_p2_phi.clear();		Lbar_p2_phi.clear();
	//-------------------------------ENTER iFile LOOP----------------------------------------------
	for(int iFile =0 ; iFile < MixEvent_Reader->InputFiles.size();iFile++){
		TFile *fin=TFile::Open(MixEvent_Reader->InputFiles[iFile].c_str(),"READ");
		if(!fin){
			std::cout<<"Can not open MixEvent_Reader file, skip."<<std::endl;
			continue;
		}
		TTree *tree = (TTree *)fin->Get("ntp_Lambda");
		if(!tree){
			std::cout<<"Can not obtain MixEvent_Reader tree,skip." <<std::endl;
			continue;
		}

		MixEvent_Reader->Init(tree);

		Long64_t N_Events=MixEvent_Reader->fChain->GetEntries();
		//------------------------------ENTER iEvent LOOP-------------------------------------
		for(int iEvent=0;iEvent<N_Events;iEvent++){
			MixEvent_Reader->fChain->GetEntry(iEvent);
			std::vector<int> GoodLambdaFlag;
			for(int i_lambda = 0; i_lambda<MixEvent_Reader->NLambda;i_lambda++){				
				TLorentzVector v;
				v.SetPtEtaPhiM(MixEvent_Reader->pair_pt[i_lambda],MixEvent_Reader->pair_eta[i_lambda],MixEvent_Reader->pair_phi[i_lambda],MixEvent_Reader->pair_mass[i_lambda]);
				int isGoodLambda = ( 
									LambdaSelecter->IsGoodLambda(MixEvent_Reader->p2_pt[i_lambda], MixEvent_Reader->p1_pt[i_lambda],
																MixEvent_Reader->p2_eta[i_lambda], MixEvent_Reader->p1_eta[i_lambda],
																MixEvent_Reader->pair_pt[i_lambda], v.Rapidity(),
																MixEvent_Reader->pair_mass[i_lambda], MixEvent_Reader->pair_decayL[i_lambda],
																MixEvent_Reader->pair_theta[i_lambda],MixEvent_Reader->pair_DCAdaughters[i_lambda])
				 				&& LambdaSelecter->IsGoodLambdaCharge(MixEvent_Reader->pair_charge[i_lambda]) 
				 				&& LambdaSelecter->IsGoodLambdaDCA(MixEvent_Reader->pair_decayL[i_lambda], MixEvent_Reader->pair_theta[i_lambda] )
				 				&& LambdaSelecter->IsGoodDauDCA(MixEvent_Reader->p1_dca[i_lambda], MixEvent_Reader->p2_dca[i_lambda] )
				 				   );
				GoodLambdaFlag.push_back(isGoodLambda);
			}

			int NGoodLambda = std::accumulate(GoodLambdaFlag.begin(), GoodLambdaFlag.end(), 0);
			if(NGoodLambda !=1) continue;

			for(int i_lambda=0;i_lambda<MixEvent_Reader->NLambda;i_lambda++){
				if(!GoodLambdaFlag[i_lambda]) continue;
				if(MixEvent_Reader->p1_ch[i_lambda] == +1 ) {
					if(L_pair_pt.size() >= MixEventPoolSize ) break;
					TLorentzVector v;
					v.SetPtEtaPhiM(MixEvent_Reader->pair_pt[i_lambda],MixEvent_Reader->pair_eta[i_lambda],MixEvent_Reader->pair_phi[i_lambda],MixEvent_Reader->pair_mass[i_lambda]);
					L_pair_pt.push_back( MixEvent_Reader->pair_pt[i_lambda]  );
					L_pair_y.push_back(  v.Rapidity()  );	
					L_pair_eta.push_back( MixEvent_Reader->pair_eta[i_lambda]  );
					L_pair_phi.push_back( MixEvent_Reader->pair_phi[i_lambda]  ) ;
					L_pair_mass.push_back( MixEvent_Reader->pair_mass[i_lambda]  );
					L_pair_charge.push_back( MixEvent_Reader->pair_charge[i_lambda]  );
	
	

					L_p1_pt.push_back( MixEvent_Reader->p1_pt[i_lambda] );
					L_p1_eta.push_back(MixEvent_Reader->p1_eta[i_lambda]);
					L_p1_phi.push_back(MixEvent_Reader->p1_phi[i_lambda]);
					L_p1_ch.push_back(MixEvent_Reader->p1_ch[i_lambda]);

					L_p2_pt.push_back(MixEvent_Reader->p1_pt[i_lambda]);
					L_p2_eta.push_back(MixEvent_Reader->p1_eta[i_lambda]);
					L_p2_phi.push_back(MixEvent_Reader->p1_phi[i_lambda]);
				}
				else{
					if(Lbar_pair_pt.size() >= MixEventPoolSize ) break;
					TLorentzVector v;
					v.SetPtEtaPhiM(MixEvent_Reader->pair_pt[i_lambda],MixEvent_Reader->pair_eta[i_lambda],MixEvent_Reader->pair_phi[i_lambda],MixEvent_Reader->pair_mass[i_lambda]);
					Lbar_pair_pt.push_back( MixEvent_Reader->pair_pt[i_lambda]  );
					Lbar_pair_y.push_back(  v.Rapidity()  );	
					Lbar_pair_eta.push_back( MixEvent_Reader->pair_eta[i_lambda]  );
					Lbar_pair_phi.push_back( MixEvent_Reader->pair_phi[i_lambda]  ) ;
					Lbar_pair_mass.push_back( MixEvent_Reader->pair_mass[i_lambda]  );
					Lbar_pair_charge.push_back( MixEvent_Reader->pair_charge[i_lambda]  );
	
	

					Lbar_p1_pt.push_back( MixEvent_Reader->p1_pt[i_lambda] );
					Lbar_p1_eta.push_back(MixEvent_Reader->p1_eta[i_lambda]);
					Lbar_p1_phi.push_back(MixEvent_Reader->p1_phi[i_lambda]);
					Lbar_p1_ch.push_back(MixEvent_Reader->p1_ch[i_lambda]);

					Lbar_p2_pt.push_back(MixEvent_Reader->p1_pt[i_lambda]);
					Lbar_p2_eta.push_back(MixEvent_Reader->p1_eta[i_lambda]);
					Lbar_p2_phi.push_back(MixEvent_Reader->p1_phi[i_lambda]);

				}
			}

			if(L_pair_pt.size() >= MixEventPoolSize && Lbar_pair_pt.size() >= MixEventPoolSize ) return;




		}
		//------------------------------END iEvent LOOP---------------------------------------


		delete fin;

	}
	//-------------------------------END iFile LOOP----------------------------------------------




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


int ntp_Lambda_Analyzer::Analyze_SEPair(int i_lambda,int j_lambda){
		if( SameEvent_Reader->p1_InEventID[i_lambda] == SameEvent_Reader->p1_InEventID[j_lambda] || 
	   		SameEvent_Reader->p1_InEventID[i_lambda] == SameEvent_Reader->p2_InEventID[i_lambda] || 
	   		SameEvent_Reader->p1_InEventID[i_lambda] == SameEvent_Reader->p2_InEventID[j_lambda] || 
	   		SameEvent_Reader->p1_InEventID[j_lambda] == SameEvent_Reader->p2_InEventID[i_lambda] || 
	   		SameEvent_Reader->p1_InEventID[j_lambda] == SameEvent_Reader->p2_InEventID[j_lambda] ||
	   		SameEvent_Reader->p2_InEventID[i_lambda] == SameEvent_Reader->p2_InEventID[j_lambda] ) return 0;
				
			

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
			return 0;
			std::cout<<"Something went wrong with the pair type classifier"<<std::endl;
		}
			
		//---------------------------Create Same-Event Pairs-------------------------------
		TLorentzVector Lambda1; Lambda1.SetPtEtaPhiM( SameEvent_Reader->pair_pt[id_Lambda1], SameEvent_Reader->pair_eta[id_Lambda1], SameEvent_Reader->pair_phi[id_Lambda1], SameEvent_Reader->pair_mass[id_Lambda1]  );
		TLorentzVector proton1; proton1.SetPtEtaPhiM( SameEvent_Reader->p1_pt[id_Lambda1]  , SameEvent_Reader->p1_eta[id_Lambda1]  , SameEvent_Reader->p1_phi[id_Lambda1]  , MASS_PROTON                              );
		TLorentzVector pion1  ;   pion1.SetPtEtaPhiM( SameEvent_Reader->p2_pt[id_Lambda1]  , SameEvent_Reader->p2_eta[id_Lambda1]  , SameEvent_Reader->p2_phi[id_Lambda1]  , MASS_PION                                );

		TLorentzVector Lambda2; Lambda2.SetPtEtaPhiM( SameEvent_Reader->pair_pt[id_Lambda2], SameEvent_Reader->pair_eta[id_Lambda2], SameEvent_Reader->pair_phi[id_Lambda2], SameEvent_Reader->pair_mass[id_Lambda2]  );
		TLorentzVector proton2; proton2.SetPtEtaPhiM( SameEvent_Reader->p1_pt[id_Lambda2]  , SameEvent_Reader->p1_eta[id_Lambda2]  , SameEvent_Reader->p1_phi[id_Lambda2]  , MASS_PROTON                              );
		TLorentzVector pion2;     pion2.SetPtEtaPhiM( SameEvent_Reader->p2_pt[id_Lambda2]  , SameEvent_Reader->p2_eta[id_Lambda2]  , SameEvent_Reader->p2_phi[id_Lambda2]  , MASS_PION                                );


		//---------------------------Range Type Classification-------------------------------
		int Range_Type  = Range_Type_Classifier(&Lambda1,&Lambda2);
			
		//Fill the pair plots 
		Histogramer->Fill_PairPlots(&Lambda1,&Lambda2,TMath::Abs(Pair_Type)-1,Range_Type);

		//Calculate the Density Matrix
		Calculator->Reset(&Lambda1,&proton1,&pion1,&Lambda2,&proton2,&pion2);
		Calculator->Calculation();

		//Fill Density Matrix Histgrams 
		Histogramer->Fill_DensityMatrix(TMath::Abs(Pair_Type)-1,Range_Type);
		return 1;
}






void ntp_Lambda_Analyzer::Analysis_SameEvent(){

	//Start looping over all inputfiles inthe SameEvent_Reader
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

			//------------------------Make some selections on the events-----------------------------
			if( !EventSelecter->IsGoodEvent() ) continue;
			//if(SameEvent_Reader->NLambda<3) continue; // current we only select on multi-Lambdas Events 
			std::vector<int> GoodLambdaFlag;
			for(int i_lambda = 0; i_lambda<SameEvent_Reader->NLambda;i_lambda++){
				
				TLorentzVector v;
				v.SetPtEtaPhiM(SameEvent_Reader->pair_pt[i_lambda],SameEvent_Reader->pair_eta[i_lambda],SameEvent_Reader->pair_phi[i_lambda],SameEvent_Reader->pair_mass[i_lambda]);

				int isGoodLambda = ( 
									LambdaSelecter->IsGoodLambda(SameEvent_Reader->p2_pt[i_lambda], SameEvent_Reader->p1_pt[i_lambda],
																SameEvent_Reader->p2_eta[i_lambda], SameEvent_Reader->p1_eta[i_lambda],
																SameEvent_Reader->pair_pt[i_lambda], v.Rapidity(),
																SameEvent_Reader->pair_mass[i_lambda], SameEvent_Reader->pair_decayL[i_lambda],
																SameEvent_Reader->pair_theta[i_lambda],SameEvent_Reader->pair_DCAdaughters[i_lambda])
				 				&& LambdaSelecter->IsGoodLambdaCharge(SameEvent_Reader->pair_charge[i_lambda]) 
				 				&& LambdaSelecter->IsGoodLambdaDCA(SameEvent_Reader->pair_decayL[i_lambda], SameEvent_Reader->pair_theta[i_lambda] )
				 				&& LambdaSelecter->IsGoodDauDCA(SameEvent_Reader->p1_dca[i_lambda], SameEvent_Reader->p2_dca[i_lambda] )
				 				   );
				GoodLambdaFlag.push_back(isGoodLambda);
			}

			int NGoodLambda = std::accumulate(GoodLambdaFlag.begin(), GoodLambdaFlag.end(), 0);
			if(NGoodLambda < 2) continue;


			//Fill Histograms of QA plot;
			Histogramer->Fill_QAplots(GoodLambdaFlag);//Notice that here, if two Lambda Candiates share some tracks, both Lambdas will be filled inthe QAplots.

			for(int i_lambda=0;i_lambda < SameEvent_Reader->NLambda;i_lambda++){
				if( GoodLambdaFlag[i_lambda] == 0 ) continue;
				for(int j_lambda=i_lambda+1;j_lambda < SameEvent_Reader->NLambda;j_lambda++){
					if( GoodLambdaFlag[j_lambda] == 0 ) continue;
					Analyze_SEPair(i_lambda,j_lambda);
				}
			}



		}
		//---------------------------End i_event loop----------------------------
		fin->Close();
		delete fin;
	}

	//-------------------------------Enter i_file loop---------------------------------

}




void ntp_Lambda_Analyzer::FindCounterparts(std::vector<TLorentzVector> *Lambda_counterpart,std::vector<TLorentzVector> *proton_counterpart,std::vector<TLorentzVector> *pion_counterpart,double rapidity,int I_LAMBDA){
	if(SameEvent_Reader->p1_ch[I_LAMBDA] == +1){
			for(int i_lambda =0 ; i_lambda < L_pair_pt.size();i_lambda++){
				if(!LambdaSelecter->IsGoodLambdaMass(L_pair_pt[i_lambda],L_pair_mass[i_lambda] )) continue;
				int isGoodCounterPart = LambdaSelecter->IsGoodLambdaCounterpart(L_pair_pt[i_lambda], SameEvent_Reader->pair_pt[I_LAMBDA],
																	  L_pair_y[i_lambda],rapidity,
																	  L_pair_phi[i_lambda], SameEvent_Reader->pair_phi[I_LAMBDA],
																	  L_pair_charge[i_lambda], SameEvent_Reader->pair_charge[I_LAMBDA],
																	  L_p1_ch[i_lambda], SameEvent_Reader->p1_ch[I_LAMBDA] );
				if(!isGoodCounterPart) continue;

				TLorentzVector lambda; lambda.SetPtEtaPhiM( L_pair_pt[i_lambda] , L_pair_eta[i_lambda] , L_pair_phi[i_lambda] , L_pair_mass[i_lambda] );
				TLorentzVector proton; proton.SetPtEtaPhiM( L_p1_pt[i_lambda]   , L_p1_eta[i_lambda]   , L_p1_phi[i_lambda]   , MASS_PROTON                   );
				TLorentzVector pion;   pion.SetPtEtaPhiM(   L_p2_pt[i_lambda]   , L_p2_eta[i_lambda]   , L_p2_phi[i_lambda]   , MASS_PION                     );

				Lambda_counterpart->push_back(lambda);
				proton_counterpart->push_back(proton);
				pion_counterpart->push_back(pion);
			}

	}
	else{
		for(int i_lambda =0 ; i_lambda < Lbar_pair_pt.size();i_lambda++){
				if(!LambdaSelecter->IsGoodLambdaMass(Lbar_pair_pt[i_lambda],Lbar_pair_mass[i_lambda] )) continue;
				int isGoodCounterPart = LambdaSelecter->IsGoodLambdaCounterpart(Lbar_pair_pt[i_lambda], SameEvent_Reader->pair_pt[I_LAMBDA],
																	  Lbar_pair_y[i_lambda],rapidity,
																	  Lbar_pair_phi[i_lambda], SameEvent_Reader->pair_phi[I_LAMBDA],
																	  Lbar_pair_charge[i_lambda], SameEvent_Reader->pair_charge[I_LAMBDA],
																	  Lbar_p1_ch[i_lambda], SameEvent_Reader->p1_ch[I_LAMBDA] );
				if(!isGoodCounterPart) continue;

				TLorentzVector lambda; lambda.SetPtEtaPhiM( Lbar_pair_pt[i_lambda] , Lbar_pair_eta[i_lambda] , Lbar_pair_phi[i_lambda] , Lbar_pair_mass[i_lambda] );
				TLorentzVector proton; proton.SetPtEtaPhiM( Lbar_p1_pt[i_lambda]   , Lbar_p1_eta[i_lambda]   , Lbar_p1_phi[i_lambda]   , MASS_PROTON                   );
				TLorentzVector pion;   pion.SetPtEtaPhiM(   Lbar_p2_pt[i_lambda]   , Lbar_p2_eta[i_lambda]   , Lbar_p2_phi[i_lambda]   , MASS_PION                     );

				Lambda_counterpart->push_back(lambda);
				proton_counterpart->push_back(proton);
				pion_counterpart->push_back(pion);
			}

	}




	

}

int ntp_Lambda_Analyzer::Analyze_MEPair(int i_lambda,int j_lambda){
		if(SameEvent_Reader->p1_InEventID[i_lambda] == SameEvent_Reader->p1_InEventID[j_lambda] || 
		   SameEvent_Reader->p1_InEventID[i_lambda] == SameEvent_Reader->p2_InEventID[i_lambda] || 
		   SameEvent_Reader->p1_InEventID[i_lambda] == SameEvent_Reader->p2_InEventID[j_lambda] || 
		   SameEvent_Reader->p1_InEventID[j_lambda] == SameEvent_Reader->p2_InEventID[i_lambda] || 
		   SameEvent_Reader->p1_InEventID[j_lambda] == SameEvent_Reader->p2_InEventID[j_lambda] ||
		   SameEvent_Reader->p2_InEventID[i_lambda] == SameEvent_Reader->p2_InEventID[j_lambda] ) return 0;

			
		if(!LambdaSelecter->IsGoodLambdaMass(SameEvent_Reader->pair_pt[i_lambda],SameEvent_Reader->pair_mass[i_lambda] ) ) return 0;
		if(!LambdaSelecter->IsGoodLambdaMass(SameEvent_Reader->pair_pt[j_lambda],SameEvent_Reader->pair_mass[j_lambda] ) ) return 0;

		//---------------------------Event Type Classification-------------------------------
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
			return 0;
			std::cout<<"Something went wrong with the pair type classifier"<<std::endl;
		}
			
		//---------------------------Create Same-Event Pairs-------------------------------
		TLorentzVector Lambda1; Lambda1.SetPtEtaPhiM( SameEvent_Reader->pair_pt[id_Lambda1], SameEvent_Reader->pair_eta[id_Lambda1], SameEvent_Reader->pair_phi[id_Lambda1], SameEvent_Reader->pair_mass[id_Lambda1]  );
		TLorentzVector proton1; proton1.SetPtEtaPhiM( SameEvent_Reader->p1_pt[id_Lambda1]  , SameEvent_Reader->p1_eta[id_Lambda1]  , SameEvent_Reader->p1_phi[id_Lambda1]  , MASS_PROTON                              );
		TLorentzVector pion1  ;   pion1.SetPtEtaPhiM( SameEvent_Reader->p2_pt[id_Lambda1]  , SameEvent_Reader->p2_eta[id_Lambda1]  , SameEvent_Reader->p2_phi[id_Lambda1]  , MASS_PION                                );

		TLorentzVector Lambda2; Lambda2.SetPtEtaPhiM( SameEvent_Reader->pair_pt[id_Lambda2], SameEvent_Reader->pair_eta[id_Lambda2], SameEvent_Reader->pair_phi[id_Lambda2], SameEvent_Reader->pair_mass[id_Lambda2]  );
		TLorentzVector proton2; proton2.SetPtEtaPhiM( SameEvent_Reader->p1_pt[id_Lambda2]  , SameEvent_Reader->p1_eta[id_Lambda2]  , SameEvent_Reader->p1_phi[id_Lambda2]  , MASS_PROTON                              );
		TLorentzVector pion2;     pion2.SetPtEtaPhiM( SameEvent_Reader->p2_pt[id_Lambda2]  , SameEvent_Reader->p2_eta[id_Lambda2]  , SameEvent_Reader->p2_phi[id_Lambda2]  , MASS_PION                                );
		//---------------------------Range Type Classification-------------------------------
		int Range_Type  = Range_Type_Classifier(&Lambda1,&Lambda2);

		//----------------------------Create Mixed-Event Pairs-------------------------------
		std::vector<TLorentzVector> Lambda1_counterpart;
		std::vector<TLorentzVector> proton1_counterpart;
		std::vector<TLorentzVector> pion1_counterpart;
		std::vector<TLorentzVector> Lambda2_counterpart;
		std::vector<TLorentzVector> proton2_counterpart;
		std::vector<TLorentzVector> pion2_counterpart;
		

		FindCounterparts(&Lambda2_counterpart,&proton2_counterpart,&pion2_counterpart,Lambda2.Rapidity(), id_Lambda2 );
		FindCounterparts(&Lambda1_counterpart,&proton1_counterpart,&pion1_counterpart,Lambda1.Rapidity(), id_Lambda1 );

		for(int k_lambda = 0; k_lambda < Lambda2_counterpart.size();k_lambda++){
			//Fill the pair plots 
			Histogramer->Fill_PairPlots(&Lambda1,&Lambda2_counterpart[k_lambda],TMath::Abs(Pair_Type)-1,Range_Type, 0.5/Lambda2_counterpart.size() );
			//Calculate the Density Matrix
			Calculator->Reset(&Lambda1,&proton1,&pion1,&Lambda2_counterpart[k_lambda],&proton2_counterpart[k_lambda],&pion2_counterpart[k_lambda]);
			Calculator->Calculation();
			Histogramer->Fill_DensityMatrix(TMath::Abs(Pair_Type)-1,Range_Type,0.5/Lambda2_counterpart.size() );
		}

		for(int k_lambda = 0; k_lambda < Lambda1_counterpart.size();k_lambda++){
			//Fill the pair plots 
			Histogramer->Fill_PairPlots(&Lambda1_counterpart[k_lambda],&Lambda2,TMath::Abs(Pair_Type)-1,Range_Type, 0.5/Lambda1_counterpart.size() );
			//Calculate the Density Matrix
			Calculator->Reset(&Lambda1_counterpart[k_lambda],&proton1_counterpart[k_lambda],&pion1_counterpart[k_lambda],&Lambda2,&proton2,&pion2);
			Calculator->Calculation();
			Histogramer->Fill_DensityMatrix(TMath::Abs(Pair_Type)-1,Range_Type,0.5/Lambda1_counterpart.size() );
		}
		return 1;

}



void ntp_Lambda_Analyzer::Analysis_MixEvent(){
	//Start looping over all inputfiles of Same_Event_Reader 
	unsigned long N_Inputfiles_SE = SameEvent_Reader->InputFiles.size();
	LLbar_USED = 0;
	Fill_MixPool();
	//-------------------------------Enter i_file loop---------------------------------
	for(unsigned i_file = 0 ;i_file < N_Inputfiles_SE ;i_file++){
		//if(i_file%1==0) std::cout<<"i_file="<<i_file<<std::endl;
		std::cout<<"i_file="<<i_file<<std::endl;
		TFile *fin= TFile::Open(SameEvent_Reader->InputFiles[i_file].c_str(),"READ");
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
		//---------------------------Ener i_event loop----------------------------
		for(Long64_t i_event=0;i_event< N_Events;i_event++){
			if(i_event%1000==0)std::cout<<"i_event"<<i_event<<std::endl;
			SameEvent_Reader->fChain->GetEntry(i_event);

			//------------------------Make some selections on the events-----------------------------
			if( !EventSelecter->IsGoodEvent() ) continue;
			//if(SameEvent_Reader->NLambda < 3) continue;// current we only select on multi-Lambdas Events
			

			std::vector<int> GoodLambdaFlag;
			for(int i_lambda = 0; i_lambda<SameEvent_Reader->NLambda;i_lambda++){
				
				TLorentzVector v;
				v.SetPtEtaPhiM(SameEvent_Reader->pair_pt[i_lambda],SameEvent_Reader->pair_eta[i_lambda],SameEvent_Reader->pair_phi[i_lambda],SameEvent_Reader->pair_mass[i_lambda]);

				int isGoodLambda = ( 
									LambdaSelecter->IsGoodLambda(SameEvent_Reader->p2_pt[i_lambda], SameEvent_Reader->p1_pt[i_lambda],
																SameEvent_Reader->p2_eta[i_lambda], SameEvent_Reader->p1_eta[i_lambda],
																SameEvent_Reader->pair_pt[i_lambda], v.Rapidity(),
																SameEvent_Reader->pair_mass[i_lambda], SameEvent_Reader->pair_decayL[i_lambda],
																SameEvent_Reader->pair_theta[i_lambda],SameEvent_Reader->pair_DCAdaughters[i_lambda])
				 				&& LambdaSelecter->IsGoodLambdaCharge(SameEvent_Reader->pair_charge[i_lambda]) 
				 				&& LambdaSelecter->IsGoodLambdaDCA(SameEvent_Reader->pair_decayL[i_lambda], SameEvent_Reader->pair_theta[i_lambda] )
				 				&& LambdaSelecter->IsGoodDauDCA(SameEvent_Reader->p1_dca[i_lambda],SameEvent_Reader->p2_dca[i_lambda])
				 				   );
				GoodLambdaFlag.push_back(isGoodLambda);
			}


			
			int NGoodLambda = std::accumulate(GoodLambdaFlag.begin(), GoodLambdaFlag.end(), 0);
			if(NGoodLambda < 2) continue;

			//Fill Histograms of QA plot;
			Histogramer->Fill_QAplots(GoodLambdaFlag);


			for(int i_lambda=0;i_lambda < SameEvent_Reader->NLambda;i_lambda++){
				if( GoodLambdaFlag[i_lambda] == 0) continue;
				for(int j_lambda=i_lambda+1;j_lambda < SameEvent_Reader->NLambda;j_lambda++){
					if( GoodLambdaFlag[j_lambda] == 0 ) continue;
					if( TMath::Abs( Pair_Type_Classifier(i_lambda, j_lambda) )==1 && LLbar_USED< 30000  ){
						Analyze_MEPair(i_lambda,j_lambda);
						LLbar_USED++;
					}

				}
			}

		}
		//---------------------------End i_event loop----------------------------
		fin->Close();
		delete fin;

	}
	//-------------------------------Enter i_file loop---------------------------------

}





#endif
