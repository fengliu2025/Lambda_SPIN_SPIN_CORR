#include "include/ntp_Lambda_Analyzer_Cali.h"
#include "include/ntp_Lambda_Histogram.h"
#include "include/ntp_Lambda_Reader.h"
#include "include/ntp_Lambda_EventSelecter.h"
#include "include/ntp_Lambda_LambdaSelecter.h"
#include <fstream>
#include <numeric>
int main(int argc, char*argv[]){





	std::vector<std::string> FileList;
	std::vector<std::string> FileName;

	
	std::ifstream filelist("/gpfs01/star/pwg/fliu/production_test/pp2024_P24iy/PicoDstLambda_P24iy/FileList.txt");

	if (!filelist.is_open()) {
		std::cerr <<"can't open the file" <<std::endl;
	}
	std::string directory="/gpfs01/star/pwg/fliu/production_test/pp2024_P24iy/PicoDstLambda_P24iy/";
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
	



	ntp_Lambda_Reader *mySameEventReader = new ntp_Lambda_Reader(InputFile_SameEvent);
	
	
	std::string OutPutFile = "Lambda_P24iyScaledMass_plot_eta1p5.root"; 
	ntp_Lambda_Histogram *myHistogram = new ntp_Lambda_Histogram(mySameEventReader,OutPutFile);
	myHistogram->Cali_scale_max = 1.000;
	myHistogram->Cali_scale_min = 0.996;
	myHistogram->Cali_NPoint    = 10;
	myHistogram->InitHitogram();

	



	ntp_Lambda_EventSelecter *myEventSelecter = new ntp_Lambda_EventSelecter();
	
	//myEventSelecter->AllowedTriggerId.push_back(910001);
	//myEventSelecter->AllowedTriggerId.push_back(910003);
	//myEventSelecter->AllowedTriggerId.push_back(910013);
	myEventSelecter->AllowedTriggerId.push_back(910802);
	myEventSelecter->AllowedTriggerId.push_back(910804);
	ntp_Lambda_LambdaSelecter *myLambdaSelecter = new ntp_Lambda_LambdaSelecter();


 	

	
	ntp_Lambda_Analyzer *myAnalyzer = new ntp_Lambda_Analyzer(mySameEventReader,myHistogram,myEventSelecter,myLambdaSelecter,1.000,0.996,10);

	//---------------
	myAnalyzer->Analysis_Cali();
	//---------------	

	myHistogram->WriteAll();
	return 0;
}
