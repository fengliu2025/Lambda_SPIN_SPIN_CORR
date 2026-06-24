#ifndef ntp_Lambda_MixTreeReader_h
#define ntp_Lambda_MixTreeReader_h


#include <vector>
#include <string>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>


class ntp_Lambda_MixTreeReader {
public :
   TTree          *fChain;  
   std::vector<std::vector< std::string > > InputFiles;



   // Declaration of leaf types
   Int_t           Lambda_Number;
   Int_t           CounterPart_Number;
   Int_t           Start_Index[50];   //[Lambda_Number]
   Int_t           End_Index[50];   //[Lambda_Number]
   Int_t           CounterPart_FileIndex[10000];   //[CounterPart_Number]
   Int_t           CounterPart_EventIndex[10000];   //[CounterPart_Number]

   // List of branches
   TBranch        *b_Lambda_Number;   //!
   TBranch        *b_CounterPart_Number;   //!
   TBranch        *b_Start_Index;   //!
   TBranch        *b_End_Index;   //!
   TBranch        *b_CounterPart_FileIndex;   //!
   TBranch        *b_CounterPart_EventIndex;   //!

   ntp_Lambda_MixTreeReader(std::vector<std::vector< std::string > > Inputfiles);
   virtual ~ntp_Lambda_MixTreeReader();
   virtual void     Init(TTree *tree);
};

ntp_Lambda_MixTreeReader::ntp_Lambda_MixTreeReader(std::vector<std::vector< std::string > > Inputfiles ) 
: fChain(0), InputFiles(Inputfiles)
{

  
}

ntp_Lambda_MixTreeReader::~ntp_Lambda_MixTreeReader()
{
   
}




void ntp_Lambda_MixTreeReader::Init(TTree *tree)
{
   
   if (!tree) return;
   fChain = tree;

   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Lambda_Number", &Lambda_Number, &b_Lambda_Number);
   fChain->SetBranchAddress("CounterPart_Number", &CounterPart_Number, &b_CounterPart_Number);
   fChain->SetBranchAddress("Start_Index", Start_Index, &b_Start_Index);
   fChain->SetBranchAddress("End_Index", End_Index, &b_End_Index);
   fChain->SetBranchAddress("CounterPart_FileIndex", CounterPart_FileIndex, &b_CounterPart_FileIndex);
   fChain->SetBranchAddress("CounterPart_EventIndex", CounterPart_EventIndex, &b_CounterPart_EventIndex);
  
}





#endif
