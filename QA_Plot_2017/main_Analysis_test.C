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

	std::ifstream filelist("/gpfs01/star/pwg/fliu/production/pp2017/PicoDstLambda_P20ic/fileList.txt");
	

	if (!filelist.is_open()) {
		std::cerr <<"can't open the file" <<std::endl;
	}
	
	std::string directory="/gpfs01/star/pwg/fliu/production/pp2017/PicoDstLambda_P20ic/";
	
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
	

	std::string OutPutFile = "Run17.root";
	ntp_Lambda_Histogram *myHistogram = new ntp_Lambda_Histogram(mySameEventReader,OutPutFile);
	myHistogram->InitHitogram();

	



	ntp_Lambda_EventSelecter *myEventSelecter = new ntp_Lambda_EventSelecter();
	

	myEventSelecter->AllowedTriggerId.push_back(570001);
	//myEventSelecter->AllowedTriggerId.push_back(570004);
	
	ntp_Lambda_LambdaSelecter *myLambdaSelecter = new ntp_Lambda_LambdaSelecter();


 	

	
	ntp_Lambda_Analyzer *myAnalyzer = new ntp_Lambda_Analyzer(mySameEventReader,myHistogram,myEventSelecter,myLambdaSelecter);
	//---------------
	myAnalyzer->Analysis_QAPlot();
	//---------------	

	myHistogram->WriteAll();
	return 0;
}
