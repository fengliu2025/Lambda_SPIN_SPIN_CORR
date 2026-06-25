#include "include/ntp_Lambda_Analyzer_v3.h"
#include "include/ntp_Lambda_Calculator.h"
#include "include/ntp_Lambda_Histogram.h"
#include "include/ntp_Lambda_Reader.h"
#include "include/ntp_Lambda_EventSelecter.h"
#include "include/ntp_Lambda_LambdaSelecter.h"
#include "include/ntp_Lambda_MixTreeReader.h"
#include <fstream>
#include <numeric>
int main(int argc, char*argv[]){


	if(argc!=2 ){
		std::cout<<"Usage: "<<argv[0]<<"file_index"<<std::endl;
		return 1;
	}
	int file_Index = std::stoi(argv[1]);




	std::vector<std::string> FileList;
	std::vector<std::string> FileName;

	std::ifstream filelist("/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2012data/MiddleTree/filelist.txt");
	if (!filelist.is_open()) {
		std::cerr <<"can't open the file" <<std::endl;
	}
	std::string directory="/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2012data/MiddleTree/";
	std::string line;
	
	while (std::getline(filelist,line)){
		FileList.push_back(directory+line);
		FileName.push_back(line);
	}

	

	std::vector<std::string> s1_tmp; 
	std::vector<std::string> s2_tmp; 
	s1_tmp.push_back(FileList[file_Index]);



	std::string MixTreeDir = "/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2012data/MiddleTree_MixTree/";
	std::string s1 = FileName[file_Index];
	std::string s2 = FileName[file_Index];

	std::size_t pos = s1.rfind(".root");

	if (pos != std::string::npos) {
    	s1.erase(pos);
	}

	
	s2_tmp.push_back(MixTreeDir+s1+"/"+s2);



	std::vector<std::string> InputFile_SameEvent; 
	std::vector<std::vector<std::string> > InputFile_MixEvent;
	std::vector<std::vector<std::string> > InputFile_MixTree;

	//InputFile_SameEvent.push_back(FileList[file_Index]);
	

	for(int i=0; i <FileList.size();i++){
		InputFile_SameEvent.push_back(FileList[i]);
	}
	
	InputFile_MixEvent.push_back(s1_tmp);
	InputFile_MixTree.push_back(s2_tmp);


	//std::string OutPutFile = std::string("/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2012Result/MixEvent/") + Form("MixEvent_%d.root",file_Index) ;
	std::string OutPutFile = "SameEvent.root";

	ntp_Lambda_Reader *mySameEventReader = new ntp_Lambda_Reader(InputFile_SameEvent);
	ntp_Lambda_Reader *myMixEventReader  = new ntp_Lambda_Reader(InputFile_MixEvent);
	ntp_Lambda_MixTreeReader *myMixTreeReader = new ntp_Lambda_MixTreeReader(InputFile_MixTree);

	ntp_Lambda_Calculator *myCalculator = new ntp_Lambda_Calculator();
	ntp_Lambda_Histogram *myHistogram = new ntp_Lambda_Histogram(mySameEventReader,myCalculator,OutPutFile);
	myHistogram->InitHitogram();

	ntp_Lambda_EventSelecter *mEventSelecter = new ntp_Lambda_EventSelecter();
	ntp_Lambda_LambdaSelecter *myLambdaSelecter = new ntp_Lambda_LambdaSelecter();


 	


	ntp_Lambda_Analyzer *myAnalyzer = new ntp_Lambda_Analyzer(mySameEventReader,myMixEventReader,myCalculator,myHistogram,myMixTreeReader,mEventSelecter,myLambdaSelecter);
	myAnalyzer->Analysis_SameEvent();
	//myAnalyzer->Analysis_MixEvent();
	myHistogram->WriteAll();
	return 0;
}
