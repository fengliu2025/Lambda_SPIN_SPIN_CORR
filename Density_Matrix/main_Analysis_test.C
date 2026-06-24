#include "include/ntp_Lambda_Analyzer_v2.h"
#include "include/ntp_Lambda_Calculator.h"
#include "include/ntp_Lambda_Histogram.h"
#include "include/ntp_Lambda_Reader.h"
#include "include/ntp_Lambda_EventSelecter.h"
#include "include/ntp_Lambda_LambdaSelecter.h"
#include "include/ntp_Lambda_MixTreeReader.h"
#include <numeric>
void main(){

	std::vector<std::string> InputFile_SameEvent; 
	std::vector<std::vector<std::string> > InputFile_MixEvent;
	std::vector<std::vector<std::string> > InputFile_MixTree;


	InputFile_SameEvent.push_back("/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2012data/MiddleTree/OutPutLittleTree_2012_OutPut_1_0.root");
	//InputFile_SameEvent.push_back("/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2012data/MiddleTree/OutPutLittleTree_2012_OutPut_1_1.root");
	//InputFile_SameEvent.push_back("/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2012data/MiddleTree/OutPutLittleTree_2012_OutPut_1_2.root");


	std::vector<std::string> s1_tmp; 
	s1_tmp.push_back("/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2012data/MiddleTree/OutPutLittleTree_2012_OutPut_1_0.root");
	s1_tmp.push_back("/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2012data/MiddleTree/OutPutLittleTree_2012_OutPut_1_1.root");
	s1_tmp.push_back("/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2012data/MiddleTree/OutPutLittleTree_2012_OutPut_1_2.root");
	std::vector<std::string> s2_tmp; 
	s2_tmp.push_back("/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2012data/MiddleTree_MixTree/OutPutLittleTree_2012_OutPut_1_0/OutPutLittleTree_2012_OutPut_1_0.root");
	s2_tmp.push_back("/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2012data/MiddleTree_MixTree/OutPutLittleTree_2012_OutPut_1_0/OutPutLittleTree_2012_OutPut_1_1.root");
	s2_tmp.push_back("/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2012data/MiddleTree_MixTree/OutPutLittleTree_2012_OutPut_1_0/OutPutLittleTree_2012_OutPut_1_2.root");

	InputFile_MixEvent.push_back(s1_tmp);
	InputFile_MixTree.push_back(s2_tmp);

	std::string OutPutFile = "MixEvent.root";


	ntp_Lambda_Reader *mySameEventReader = new ntp_Lambda_Reader(InputFile_SameEvent);
	ntp_Lambda_Reader *myMixEventReader  = new ntp_Lambda_Reader(InputFile_MixEvent);
	ntp_Lambda_MixTreeReader *myMixTreeReader = new ntp_Lambda_MixTreeReader(InputFile_MixTree);

	ntp_Lambda_Calculator *myCalculator = new ntp_Lambda_Calculator();
	ntp_Lambda_Histogram *myHistogram = new ntp_Lambda_Histogram(mySameEventReader,myCalculator,OutPutFile);
	myHistogram->InitHitogram();

	ntp_Lambda_EventSelecter *mEventSelecter = new ntp_Lambda_EventSelecter();
	ntp_Lambda_LambdaSelecter *myLambdaSelecter = new ntp_Lambda_LambdaSelecter();


 	


	ntp_Lambda_Analyzer *myAnalyzer = new ntp_Lambda_Analyzer(mySameEventReader,myMixEventReader,myCalculator,myHistogram,myMixTreeReader,mEventSelecter,myLambdaSelecter);
	//myAnalyzer->Analysis_SameEvent();
	myAnalyzer->Analysis_MixEvent();
	myHistogram->WriteAll();

}
