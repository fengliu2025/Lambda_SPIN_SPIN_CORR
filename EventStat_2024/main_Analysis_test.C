#include <fstream>
#include <numeric>
#include <vector>
#include <string>
#include "TFile.h"
#include "TList.h"
#include "TH1F.h"

int main(int argc, char*argv[]){


	if(argc!=2 ){
		std::cout<<"Usage: "<<argv[0]<<"file_index"<<std::endl;
		return 1;
	}
	int file_Index = std::stoi(argv[1]);




	std::vector<std::string> FileList;
	std::vector<std::string> FileName;

	std::ifstream filelist("/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2024data/MiddleTree/filelist.txt");
	if (!filelist.is_open()) {
		std::cerr <<"can't open the file" <<std::endl;
	}
	std::string directory="/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2024data/MiddleTree/";
	std::string line;
	
	while (std::getline(filelist,line)){
		FileList.push_back(directory+line);
		FileName.push_back(line);
	}


	TH1F *hEventStat0 = 0 ;
	TH1F *hEventStat1 = 0 ;

	for(int i=0 ; i < FileList.size();i++){
		TFile *fin =TFile::Open();
		TList *list = (TList*)fin->Get("picoLambdaAnaMaker");
		TH1F*h0 = (TH1F*)list->FindObject("hEventStat0");
		TH1F*h1 = (TH1F*)list->FindObject("hEventStat1");


		if(i==0){
			hEventStat0 = (TH1F*)h0->Clone("hEventStat0_sum"); hEventStat0 ->SetDirectory(nullptr);
			hEventStat1 = (TH1F*)h1->Clone("hEventStat1_sum"); hEventStat1 ->SetDirectory(nullptr);
		}

		else {
			hEventStat0 ->Add(h0);
			hEventStat1 ->Add(h1);
		}

		fin->Close();
		delete fin;
	}


	//-----------
	std::string OutPutFile = "SameEvent_NEW_ALL.root";   //Same Event
	//-----------
	TFile *fout = TFile::Open(OutPutFile.c_str(),"RECREATE");

	hEventStat0 ->Write();
	hEventStat1 ->Write();
	fout->Close();

	
	return 0;
}
