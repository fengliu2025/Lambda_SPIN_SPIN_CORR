#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include "TFile.h"
#include "TList.h"
#include "TH1F.h"

int main(int argc, char*argv[]){


	
	


	std::vector<std::string> FileList;
	std::vector<std::string> FileName;

	std::ifstream filelist("/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2024data/FileList.txt");
	if (!filelist.is_open()) {
		std::cerr <<"can't open the file" <<std::endl;
	}
	std::string directory="/star/u/starkong/gpfs01/forFeng/LambdaTreeProduction/pp2024_P24iy/STAR_Production/production/pp2024/PicoDstLambda_P24iy_wTrk/";
	std::string line;
	
	while (std::getline(filelist,line)){
		FileList.push_back(directory+line);
		FileName.push_back(line);
	}


	TH1F *hEventStat0 = 0 ;
	TH1F *hEventStat1 = 0 ;

	for(int i=0; i < FileList.size();i++){
		if(i%100==0) std::cout << "i=" << i <<std::endl;
		TFile *fin =TFile::Open(FileList[i].c_str());
		TList *list = (TList*)fin->Get("picoLambdaAnaMaker");
		TH1F*h0 = (TH1F*)list->FindObject("hEventStat0");
		TH1F*h1 = (TH1F*)list->FindObject("hEventStat1");
		h0->GetXaxis()->SetBinLabel(7, "");
		h1->GetXaxis()->SetBinLabel(7, "");
		//h0->GetXaxis()->SetNoAlphanumeric();
		//h1->GetXaxis()->SetNoAlphanumeric();
		if(i==0){
			hEventStat0 = (TH1F*)h0->Clone("hEventStat0_sum"); hEventStat0 ->SetDirectory(nullptr);
		
			hEventStat1 = (TH1F*)h1->Clone("hEventStat1_sum"); hEventStat1 ->SetDirectory(nullptr);
		
			for (int j = 1; j <= h1->GetNbinsX(); ++j) {
				std::cout << j << " : "
         		<< h1->GetXaxis()->GetBinLabel(j)
         		<< std::endl;
			}
		}

		else {
			hEventStat0 ->Add(h0);
			hEventStat1 ->Add(h1);
		}

		fin->Close();
		delete list;
		
		//delete h1;
		delete fin;
	}


	//-----------
	std::string OutPutFile = "EventStat.root";   //Same Event
	//-----------
	TFile *fout = TFile::Open(OutPutFile.c_str(),"RECREATE");

	hEventStat0 ->Write();
	hEventStat1 ->Write();
	fout->Close();

	
	return 0;
}
