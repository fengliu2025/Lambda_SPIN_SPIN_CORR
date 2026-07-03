#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <TChain.h>
#include <TTree.h>
#include <TFile.h>



int main(){
	std::ifstream filelist("Inputfilelist.txt");
	if(!filelist.is_open()){
		std::cerr<<"Can not open the file" << std::endl;
	}

	std::vector<std::string> InputFile;
	std::string line;

	while(std::getline(filelist,line)){
		InputFile.push_back(line);
	}

	std::vector<std::vector<std::string>> RunList;
	std::vector<int> RunID;
	int N1 = 2; 
	int N2 = 3; 

	while(InputFile.size()>0){
		std::vector<std::string> tmp_RunList;
		std::string tmp_runID_string = InputFile[0].substr(N1,N2);
		int tmp_runID = std::stoi(tmp_runID_string);
		tmp_RunList.push_back(InputFile[0]);
		InputFile.erase(InputFile.begin());
		RunID.push_back(tmp_runID);

		for(int i=0; i < InputFile.size();i++){
			std::string runID_string = InputFile[i].substr(N1,N2);
			int runID = std::stoi(runID_string);
			if(runID == tmp_runID){
				tmp_RunList.push_back(InputFile[i]);
				InputFile.erase(InputFile.begin()+i);
				i--;
			}
		}

		RunList.push_back(tmp_RunList);
	}


	std::cout<<"Number of Run: "<<RunID.size()<<std::endl;


	for(int i =0 ; i < RunID.size();i++){
		TChain chain("ntp_Lambda");
		for(int j =0 ;j < RunList[i].size();j++){
			chain.Add( RunList[i].c_str() );
		}
		chain.Merge(Form("/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2024data/DayTree/25%dpicoLambda.root"),runID[i]);
	}

	return 0;
}
