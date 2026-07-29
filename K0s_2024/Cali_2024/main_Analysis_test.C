#include "include/ntp_K0s_Analyzer_Cali.h"
#include "include/ntp_K0s_Histogram.h"
#include "include/ntp_K0s_Reader_v2.h"
#include "include/ntp_K0s_EventSelecter.h"
#include "include/ntp_K0s_K0sSelecter.h"
#include <fstream>
#include <numeric>
int main(int argc, char*argv[]){





	std::vector<std::string> FileList;
	std::vector<std::string> FileName;

	
	std::ifstream filelist("/gpfs01/star/pwg/fliu/production/pp2024/PicoDstK0s_P24iy_wTrk/FileList.txt");

	if (!filelist.is_open()) {
		std::cerr <<"can't open the file" <<std::endl;
	}
	std::string directory="/gpfs01/star/pwg/fliu/production/pp2024/PicoDstK0s_P24iy_wTrk/";
	std::string line;
	
	while (std::getline(filelist,line)){
		FileList.push_back(directory+line);
		FileName.push_back(line);
	}
	

	



	std::vector<std::string> InputFile_SameEvent; 
	//-----------

	for(int i=0; i <FileList.size();i++){
		InputFile_SameEvent.push_back(FileList[i]);      // Same Event
	}
	



	ntp_K0s_Reader *mySameEventReader = new ntp_K0s_Reader(InputFile_SameEvent);
	
	
	std::string OutPutFile = "K0s_P24iyHelixScaledMass_plot_eta1p5.root"; 
	ntp_K0s_Histogram *myHistogram = new ntp_K0s_Histogram(mySameEventReader,OutPutFile);
	myHistogram->Cali_scale_max = 1.000;
	myHistogram->Cali_scale_min = 0.995;
	myHistogram->Cali_NPoint    = 10;
	myHistogram->InitHitogram();

	



	ntp_K0s_EventSelecter *myEventSelecter = new ntp_K0s_EventSelecter();
	
	//myEventSelecter->AllowedTriggerId.push_back(910001);
	//myEventSelecter->AllowedTriggerId.push_back(910003);
	//myEventSelecter->AllowedTriggerId.push_back(910013);
	myEventSelecter->AllowedTriggerId.push_back(910802);
	myEventSelecter->AllowedTriggerId.push_back(910804);
	ntp_K0s_K0sSelecter *myK0sSelecter = new ntp_K0s_K0sSelecter();


 	

	
	ntp_K0s_Analyzer *myAnalyzer = new ntp_K0s_Analyzer(mySameEventReader,myHistogram,myEventSelecter,myK0sSelecter,1.000,0.995,10);

	//---------------
	myAnalyzer->Analysis_Cali();
	//---------------	

	myHistogram->WriteAll();
	return 0;
}
