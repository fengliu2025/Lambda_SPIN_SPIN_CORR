#ifndef ntp_Lambda_MixTree_h 
#define ntp_Lambda_MixTree_h 


#include <iostream>
#include <vector>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TLorentzVector.h>

#include "ntp_Lambda_Reader.h"
#include "ntp_Lambda_EventSelecter.h"
#include "ntp_Lambda_LambdaSelecter.h"

class ntp_Lambda_MixTree{
public : 
	//class memeber variables 
	//the directory where the output file will be 
	
	std::vector<std::string> OutPutFiles;
	TFile *fout;
	TTree *MixTree; 
	Int_t Lambda_Number; 
	Int_t CounterPart_Number;


	Int_t Start_Index[1000]; 
	Int_t End_Index[1000]; 
	Int_t CounterPart_FileIndex[1000];
	Int_t CounterPart_EventIndex[1000]; 
	//Int_t CounterPart_LambdaIndex[1000];



	std::vector<float> MixLambdaPool_Pt;
	std::vector<float> MixLambdaPool_Phi;
	std::vector<float> MixLambdaPool_Rapidity;
	std::vector<int>   MixLambdaPool_LambdaCharge;
	std::vector<int>   MixLambdaPool_DauProtonCharge;
	std::vector<int>   MixLambdaPool_FileIndex;
	std::vector<int>   MixLambdaPool_EventIndex;


	ntp_Lambda_Reader *reader_Same;
	ntp_Lambda_Reader *reader_Mix;

	ntp_Lambda_EventSelecter *mEventSelecter;
	ntp_Lambda_LambdaSelecter *mLambdaSelecter;


	//class memeber functions 

	ntp_Lambda_MixTree(std::vector<std::string> outputfiles, ntp_Lambda_Reader *mReaderS, ntp_Lambda_Reader *mReaderM, ntp_Lambda_EventSelecter *mEventSelect, ntp_Lambda_LambdaSelecter *mLambdaSelect);
	virtual ~ntp_Lambda_MixTree();
	int Init(std::string outputfile);
	void ClearPool();
	int PrePareMixPool();
	int FindCounterPart(int lambda_index);
	void GenerateMixTree();




};


ntp_Lambda_MixTree::ntp_Lambda_MixTree(std::vector<std::string> outputfiles, ntp_Lambda_Reader *mReaderS, ntp_Lambda_Reader *mReaderM, ntp_Lambda_EventSelecter *mEventSelect, ntp_Lambda_LambdaSelecter *mLambdaSelect)
:OutPutFiles(outputfiles),reader_Same(mReaderS),reader_Mix(mReaderM),mEventSelecter(mEventSelect) , mLambdaSelecter(mLambdaSelect)
{

	MixLambdaPool_Pt.clear();
	MixLambdaPool_Phi.clear();
	MixLambdaPool_Rapidity.clear();
	MixLambdaPool_LambdaCharge.clear();
	MixLambdaPool_DauProtonCharge.clear();
	MixLambdaPool_FileIndex.clear();
	MixLambdaPool_EventIndex.clear();

}


void ntp_Lambda_MixTree::ClearPool(){
	MixLambdaPool_Pt.clear();
	MixLambdaPool_Phi.clear();
	MixLambdaPool_Rapidity.clear();
	MixLambdaPool_LambdaCharge.clear();
	MixLambdaPool_DauProtonCharge.clear();
	MixLambdaPool_FileIndex.clear();
	MixLambdaPool_EventIndex.clear();

}

int ntp_Lambda_MixTree::PrePareMixPool(){
	ClearPool();

	//---------------------------Enter the loop over of MixEvent file--------------------------------------------------
	for(int iFileMix=0; iFileMix < reader_Mix->InputFiles.size(); iFileMix++){
		TFile *fin_mix = TFile::Open(reader_Mix->InputFiles[iFileMix].c_str(),"READ");
		if(!fin_mix){
			std::cout<<"Can not open the mixEvent file: "<<reader_Mix->InputFiles[iFileMix]<<", skip. "<<std::endl;
			continue;
		}
		TTree *tmp_MixTree = (TTree *)fin_mix->Get("ntp_Lambda");
		if(!tmp_MixTree){
			std::cout<<"Can not get the mixtree, skip."<<std::endl;
		}
		reader_Mix->Init(tmp_MixTree);

		Long64_t NEventsMix = reader_Mix->fChain->GetEntries();
		//------------------------------Enter the loop of event ----------------------------------------
		for(int iEventMix =0 ; iEventMix < NEventsMix; iEventMix++){
			reader_Mix->fChain->GetEntry(iEventMix);
			if(reader_Mix->NLambda!=1) continue; // only select the one-lambda event 


			if(! mEventSelecter->IsGoodEvent() ) continue; 


			TLorentzVector v_Mix;
			v_Mix.SetPtEtaPhiM(reader_Mix->pair_pt[0],reader_Mix->pair_eta[0],reader_Mix->pair_phi[0],reader_Mix->pair_mass[0]);

			if(! mLambdaSelecter->IsGoodLambda(   reader_Mix->p2_pt[0] , reader_Mix->p1_pt[0], 
												  reader_Mix->p2_eta[0], reader_Mix->p1_eta[0], 
												  reader_Mix->pair_pt[0],v_Mix.Rapidity()		      ,
												  reader_Mix->pair_mass[0], reader_Mix->pair_decayL[0],
												  reader_Mix->pair_theta[0],reader_Mix->pair_DCAdaughters[0]) ) continue;
			
			MixLambdaPool_Pt.push_back(reader_Mix->pair_pt[0]);
			MixLambdaPool_Phi.push_back(reader_Mix->pair_phi[0]);
			MixLambdaPool_Rapidity.push_back(v_Mix.Rapidity());
			MixLambdaPool_LambdaCharge.push_back(reader_Mix->pair_charge[0]);
			MixLambdaPool_DauProtonCharge.push_back(reader_Mix->p1_ch[0]);
			MixLambdaPool_FileIndex.push_back(iFileMix);
			MixLambdaPool_EventIndex.push_back(iEventMix);
			
			
			


		}
		//------------------------------Enter the loop of event ----------------------------------------



		delete fin_mix;
	}
	//---------------------------End the loop over of MixEvent file--------------------------------------------------


	std::cout<<"--------------------------------------"<<std::endl;
	std::cout<<"The memory used by the pool:"<< (
											    	( MixLambdaPool_Pt.size() + MixLambdaPool_Phi.size() + MixLambdaPool_Rapidity.size() ) *sizeof(float) + 
													( MixLambdaPool_LambdaCharge.size() + MixLambdaPool_DauProtonCharge.size() +MixLambdaPool_FileIndex.size() + MixLambdaPool_EventIndex.size() ) *sizeof(int)
												)/1024./1024.
											 << "MB" <<std::endl;
	std::cout<<"--------------------------------------"<<std::endl;					
	return 0;


}



ntp_Lambda_MixTree::~ntp_Lambda_MixTree(){

}


int ntp_Lambda_MixTree::Init(std::string outputfile){
	fout = TFile::Open(outputfile.c_str(),"RECREATE");
	fout->cd();
	MixTree = new TTree("ntp_Lambda_MixTree","ntp_Lambda_MixTree");

	MixTree->Branch("Lambda_Number",&Lambda_Number,"Lambda_Number/I");
	MixTree->Branch("CounterPart_Number",&CounterPart_Number,"CounterPart_Number/I");
 	MixTree->Branch("Start_Index",Start_Index,"Start_Index[Lambda_Number]/I");
	MixTree->Branch("End_Index",  End_Index  ,"End_Index[Lambda_Number]/I"  );
	MixTree->Branch("CounterPart_FileIndex",CounterPart_FileIndex,"CounterPart_FileIndex[CounterPart_Number]/I");
	MixTree->Branch("CounterPart_EventIndex",CounterPart_EventIndex,"CounterPart_EventIndex[CounterPart_Number]/I");
	//MixTree->Branch("CounterPart_LambdaIndex",CounterPart_LambdaIndex,"CounterPart_LambdaIndex[CounterPart_Number]/I");
	return 0;


}



int ntp_Lambda_MixTree::FindCounterPart(int lambda_index){


	TLorentzVector v;
	v.SetPtEtaPhiM(reader_Same->pair_pt[lambda_index],reader_Same->pair_eta[lambda_index],reader_Same->pair_phi[lambda_index],reader_Same->pair_mass[lambda_index]);



	bool goodness = mLambdaSelecter->IsGoodLambda(reader_Same->p2_pt[lambda_index] , reader_Same->p1_pt[lambda_index], 
												  reader_Same->p2_eta[lambda_index], reader_Same->p1_eta[lambda_index], 
												  reader_Same->pair_pt[lambda_index],v.Rapidity()					 ,
												  reader_Same->pair_mass[lambda_index], reader_Same->pair_decayL[lambda_index],
												  reader_Same->pair_theta[lambda_index],reader_Same->pair_DCAdaughters[lambda_index]);


		    
	if( goodness == false){
		Start_Index[lambda_index] = CounterPart_Number;
		End_Index[lambda_index]   = CounterPart_Number;
		return 0;
	} 

	// if the goodness is true
	//loop over the pool
	Start_Index[lambda_index] = CounterPart_Number; 

	for(int iPool=0; iPool<MixLambdaPool_Pt.size(); iPool++){
			if(! mLambdaSelecter->IsGoodLambdaCounterpart( MixLambdaPool_Pt[iPool], reader_Same->pair_pt[lambda_index],
											               MixLambdaPool_Rapidity[iPool],       v.Rapidity(),
														   MixLambdaPool_Phi[iPool],reader_Same->pair_phi[lambda_index],
														   MixLambdaPool_LambdaCharge[iPool],reader_Same->pair_charge[lambda_index],
														   MixLambdaPool_DauProtonCharge[iPool], reader_Same->p1_ch[lambda_index]	) ) continue;

			
			
			CounterPart_FileIndex[CounterPart_Number] = MixLambdaPool_FileIndex[iPool]  ;
			CounterPart_EventIndex[CounterPart_Number]= MixLambdaPool_EventIndex[iPool] ; 
			CounterPart_Number ++;


	}

	End_Index[lambda_index] = CounterPart_Number ; 

	return 0;

}







void ntp_Lambda_MixTree::GenerateMixTree(){
	//-----------------------------Enter the File LOOP---------------------------------------
	PrePareMixPool();

	for(int iFile =0 ; iFile < reader_Same->InputFiles.size();iFile++){
		TFile *fin = TFile::Open(reader_Same->InputFiles[iFile].c_str(),"READ");
		if(!fin){
			std::cout<<"The file: "<< reader_Same->InputFiles[iFile]<<" can not be opened, skip this file."<<std::endl;
			continue;
		}
		TTree *tree_same = (TTree *)fin->Get("ntp_Lambda");
		if(!tree_same){
			std::cout<<"Can not get the tree,skip this file."<<std::endl;
			continue;
		}

		reader_Same->Init(tree_same);

		Long64_t NEvents = reader_Same->fChain->GetEntries();
		Init(OutPutFiles[iFile]);

		//------------------------------------Enter the Event Loop------------------------------------
		for(Long64_t iEvent=0; iEvent< NEvents;iEvent++){
			if(iEvent%1000==0) std::cout<<"iEvent="<<iEvent<<std::endl;
			reader_Same->fChain->GetEntry(iEvent);
			// Event selection
			if( ! mEventSelecter->IsGoodEvent() ) continue;// this is not a good event
			
			Lambda_Number = reader_Same->NLambda; 
			CounterPart_Number = 0;

			//------------------------------------Enter the Lambda Loop------------------------------------
			for(int iLambda=0; iLambda < reader_Same->NLambda;iLambda++){
				if(reader_Same->NLambda==1 ) break;
				//find the mixEvent counterpart
				FindCounterPart(iLambda);
			}
			//------------------------------------End the Lambda Loop------------------------------------

			MixTree->Fill();

		}
		//------------------------------------End the Event Loop------------------------------------
		fout->cd();
		MixTree->Write();
		fout->Close();
		fin->Close();

		
		delete fout;
		delete fin;

		MixTree= nullptr;
		fout = nullptr;


	}
	//-----------------------------End the File LOOP---------------------------------------

	ClearPool();

}




#endif