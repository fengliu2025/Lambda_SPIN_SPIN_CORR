#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "include/ntp_Lambda_Reader.h"
#include "include/ntp_Lambda_EventSelecter.h"
#include "include/ntp_Lambda_LambdaSelecter.h"
#include "include/ntp_Lambda_MixTree_v2.h"





int main(int argc, char* argv[]){

	if(argc!=3 ){
		std::cout<<"Usage: "<<argv[0]<<" main_file_index mix_file_index"<<std::endl;
		return 1;
	}

	int mainIndex = std::stoi(argv[1]);
	int mixIndex  = std::stoi(argv[2]);

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




	std::vector<std::string> InFile_ReaderSame ;
	std::vector<std::string> InFile_ReaderMix ;


	InFile_ReaderSame.push_back(FileList[mainIndex]);
	InFile_ReaderMix.push_back(FileList[mixIndex]);


	//-----------------------generate the output directory------------
	std::string OutPutDirectory = "/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2012data/MiddleTree_MixTree/";
	std::string s1 = FileName[mainIndex];
	std::string s2 = FileName[mixIndex];

	std::size_t pos = s1.rfind(".root");

	if (pos != std::string::npos) {
    	s1.erase(pos);
	}

	std::vector<std::string> OutFile_MixTree;
	OutFile_MixTree.push_back(OutPutDirectory+s1+"/"+s2);



	ntp_Lambda_Reader *myReaderSame = new ntp_Lambda_Reader(InFile_ReaderSame);
	ntp_Lambda_Reader *myReaderMix  = new ntp_Lambda_Reader(InFile_ReaderMix );


	ntp_Lambda_EventSelecter *myEventSelecter = new ntp_Lambda_EventSelecter();
	ntp_Lambda_LambdaSelecter *myLambdaSelecter = new ntp_Lambda_LambdaSelecter();



	
	ntp_Lambda_MixTree * myLambdaMixTree = new ntp_Lambda_MixTree(OutFile_MixTree,myReaderSame,myReaderMix,myEventSelecter,myLambdaSelecter);

	myLambdaMixTree->GenerateMixTree();

	return 0;
}
