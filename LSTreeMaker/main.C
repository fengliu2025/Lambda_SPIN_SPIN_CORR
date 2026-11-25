#include <iostream>
#include <string>
#include <vector>
#include <fstream>


#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include "ntp_Lambda_Reader.h"

int main(){

        int Event_Max = 6000000;

        std::ifstream filelist("/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2024data_Aug09_v2/DayTree/Inputfilelist.txt");
        if(!filelist.is_open()){
                std::cerr<<"Can not open the file" <<std::endl;
        }

        std::vector<std::string> InputFile;
        std::vector<std::string> InputFileName;
        std::string line;
        std::string Directory = "/gpfs01/star/pwg/fliu/LL_Spin_Correlation/2024data_Aug09_v2/DayTree/";
        while(std::getline(filelist,line)){
                InputFile.push_back(Directory+ line);
                InputFileName.push_back(line);
        }




        for(int i =0; i < InputFile.size();i++){
                TFile *fin=TFile::Open(InputFile[i].c_str(),"READ");
                if(!fin){
                        std::cout << " Can not open file:"<< InputFile[i] <<", skip."<<std::endl;
                        continue;
                }
                TTree *InTree = (TTree *)fin->Get("ntp_Lambda");
                if(!InTree){
                        std::cout << "Can not obtain the tree,skip." << std::endl;
                }

                ntp_Lambda_Reader Reader;
                Reader.Init(InTree);

                int NEvents = InTree->GetEntries();

                int nFiles = (NEvents + Event_Max - 1) / Event_Max;

                std::string DayNumber_str = InputFileName[i].substr(2,3);
                int DayNumber = std::stoi(DayNumber_str);


                std::cout<<"InputFile: "<<i <<" . Total Entries=" << NEvents<<". N_outFile="<<nFiles<<std::endl;
                for(int ifile=0; ifile< nFiles;ifile++ ){
                        TFile *fout = TFile::Open(Form("25%d_%d_picoLSLambda.root",DayNumber,ifile),"RECREATE");
                        TTree *OutTree = InTree->CloneTree(0);
                        int i_start = ifile * Event_Max;
                        int i_end   = std::min( i_start + Event_Max, NEvents);

                        for(int ievent = i_start ; ievent <i_end; ievent++){
                                InTree->GetEntry(ievent);
                                bool IfFill = false;
                                if(Reader.NLambda==1) IfFill = true; // single Lambda pool 
                                if(Reader.NLambda>1){
                                        for(int iLam=0; iLam < Reader.NLambda;iLam++){
                                                if(Reader.pair_charge[iLam]!=0) IfFill = true;
                                        }
                                } // pair pool , required to have at least one LS Lambda
                                if(IfFill) OutTree->Fill();
                        }

                        OutTree->Write();
                        fout->Close();

                }
        }


        return 0;


}
