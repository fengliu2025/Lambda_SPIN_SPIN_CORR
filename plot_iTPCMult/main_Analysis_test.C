#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TLorentzVector.h>
 
#include <vector>
#include <string>
#include <iostream>
#include <numeric>
#include <fstream>

int main(int argc, char*argv[]){





	std::vector<std::string> FileList;
	std::vector<std::string> FileName;

	std::ifstream filelist("/gpfs01/star/pwg/fliu/production/pp2024/PicoDstLambdaXi_P24iy_wTrk/fileList.txt");
	


	if (!filelist.is_open()) {
		std::cerr <<"can't open the file" <<std::endl;
	}
	
	std::string directory="/gpfs01/star/pwg/fliu/production/pp2024/PicoDstLambdaXi_P24iy_wTrk/";
	std::string line;
	
	while (std::getline(filelist,line)){
		FileList.push_back(directory+line);
		FileName.push_back(line);
	}

	

	std::vector<std::string> InputFile_SameEvent; 
	//-----------

	for(int i=0; i <FileList.size();i++){
		InputFile_SameEvent.push_back(FileList[i]);     
	}



	TH2D *h2D_iTPCPrimaryMult_Trigger_sum      = new TH2D("h2D_iTPCPrimaryMult_Trigger_sum","h2D_iTPCPrimaryMult_Trigger_sum",100,-0.5,99.5,5,-0.5,4.5);
    TH2D *h2D_iTPCPrimaryMultHighQ_Trigger_sum = new TH2D("h2D_iTPCPrimaryMultHighQ_Trigger_sum","h2D_iTPCPrimaryMultHighQ_Trigger_sum",100,-0.5,99.5,5,-0.5,4.5);


	for(int i =0 ; i < InputFile_SameEvent.size();i++){
		TFile *fin = TFile::Open(InputFile_SameEvent[i].c_str(),"READ");
		if(!fin) {
			std::cout<<"The file can not be opened, skip"<<std::end;
			continue;
		}

		h2D_iTPCPrimaryMult_Trigger_sum      ->Add( (TH2D*)fin->Get("h2D_iTPCPrimaryMult_Trigger") );
        h2D_iTPCPrimaryMultHighQ_Trigger_sum ->Add( (TH2D*)fin->Get("h2D_iTPCPrimaryMultHighQ_Trigger") );

        fin->Close();
        delete fin;


	}

	TFile *fout = TFile::Open("MultiDistribution.root","RECREATE");

	h2D_iTPCPrimaryMult_Trigger_sum      ->Write();
    h2D_iTPCPrimaryMultHighQ_Trigger_sum ->Write();

    fout->Close();
    delete fout;



	return 0;
}
