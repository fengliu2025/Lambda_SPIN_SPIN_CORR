#include "include/ntp_Lambda_Analyzer_QA.h"
#include "include/ntp_Lambda_Histogram.h"
#include "include/ntp_Lambda_Reader_v3.h"
#include "include/ntp_Lambda_EventSelecter.h"
#include "include/ntp_Lambda_LambdaSelecter.h"
#include <fstream>
#include <numeric>
int main(int argc, char*argv[]){





	std::vector<std::string> FileList;
	std::vector<std::string> FileName;

	std::ifstream filelist("/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2024data/MiddleTree/filelist.txt");
	
	//std::ifstream filelist("/gpfs01/star/pwg/fliu/production/pp2024/PicoDstLambda_P24iy_woTrk/filelist.txt");
	//std::ifstream filelist("/gpfs01/star/pwg/fliu/production/pp2012/PicoDstLambda_P12id/FileList.txt");
	//std::ifstream filelist("/gpfs01/star/pwg/fliu/production_test/pp2024_P24iy/PicoDstLambda_P24iy/FileList.txt");

	if (!filelist.is_open()) {
		std::cerr <<"can't open the file" <<std::endl;
	}
	std::string directory="/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2024data/MiddleTree/";
	//std::string directory="/gpfs01/star/pwg/fliu/production/pp2024/PicoDstLambda_P24iy_woTrk/";
	//std::string directory="/gpfs01/star/pwg/fliu/production/pp2012/PicoDstLambda_P12id/";
	//std::string directory="/gpfs01/star/pwg/fliu/production_test/pp2024_P24iy/PicoDstLambda_P24iy/";
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
	
	//std::string OutPutFile = "PreSelectionQA_plot_MB.root"; 
	//std::string OutPutFile = "AfterSelectionQA_plot_HM_eta1p0.root"; 
	//std::string OutPutFile = "AfterSelectionMass_plot_MB_eta1p0.root"; 
	//std::string OutPutFile = "P24iyHelixAfterSelectionMass_plot_HM_eta1p0.root"; 
	//std::string OutPutFile = "SLAfterSelectionMass_plot_MB_eta1p0.root"; 
	//std::string OutPutFile = "P12idHelixAfterSelectionMass_plot_eta1p0.root"; 
	std::string OutPutFile = "P24iyAfterSelection_plot_eta1p5_HM_Window.root"; 
	ntp_Lambda_Histogram *myHistogram = new ntp_Lambda_Histogram(mySameEventReader,OutPutFile);
	myHistogram->InitHitogram();

	



	ntp_Lambda_EventSelecter *myEventSelecter = new ntp_Lambda_EventSelecter();
	
	//myEventSelecter->AllowedTriggerId.push_back(910001);
	//myEventSelecter->AllowedTriggerId.push_back(910003);
	//myEventSelecter->AllowedTriggerId.push_back(910013);
	myEventSelecter->AllowedTriggerId.push_back(910802);
	myEventSelecter->AllowedTriggerId.push_back(910804);
	//myEventSelecter->AllowedTriggerId.push_back(370001);
	//myEventSelecter->AllowedTriggerId.push_back(370011);
	ntp_Lambda_LambdaSelecter *myLambdaSelecter = new ntp_Lambda_LambdaSelecter();


 	

	
	ntp_Lambda_Analyzer *myAnalyzer = new ntp_Lambda_Analyzer(mySameEventReader,myHistogram,myEventSelecter,myLambdaSelecter);
	//---------------
	myAnalyzer->Analysis_QAPlot();
	//---------------	

	myHistogram->WriteAll();
	return 0;
}
