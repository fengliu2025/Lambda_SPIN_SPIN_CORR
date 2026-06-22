#include "include/ntp_Lambda_Reader.h"
#include "include/ntp_Lambda_EventSelecter.h"
#include "include/ntp_Lambda_LambdaSelecter.h"
#include "include/ntp_Lambda_MixTree.h"





int main(){
	std::vector<std::string> InFile_ReaderSame ;
	std::vector<std::string> InFile_ReaderMix ;

	InFile_ReaderSame.push_back("25122005_0.root.picoLambdaAnaMaker.root");
	InFile_ReaderMix.push_back("25122005_0.root.picoLambdaAnaMaker.root");



	ntp_Lambda_Reader *myReaderSame = new ntp_Lambda_Reader(InFile_ReaderSame);
	ntp_Lambda_Reader *myReaderMix  = new ntp_Lambda_Reader(InFile_ReaderMix );


	ntp_Lambda_EventSelecter *myEventSelecter = new ntp_Lambda_EventSelecter();
	ntp_Lambda_LambdaSelecter *myLambdaSelecter = new ntp_Lambda_LambdaSelecter();



	std::vector<std::string> OutFile_MixTree;

	OutFile_MixTree.push_back("MixTree.root");

	ntp_Lambda_MixTree * myLambdaMixTree = new ntp_Lambda_MixTree(OutFile_MixTree,myReaderSame,myReaderMix,myEventSelecter,myLambdaSelecter);

	myLambdaMixTree->GenerateMixTree();


}