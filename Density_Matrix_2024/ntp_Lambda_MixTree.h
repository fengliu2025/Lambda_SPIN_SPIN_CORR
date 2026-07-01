//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jun 22 00:07:42 2026 by ROOT version 6.34.08
// from TTree ntp_Lambda_MixTree/ntp_Lambda_MixTree
// found on file: MixTree.root
//////////////////////////////////////////////////////////

#ifndef ntp_Lambda_MixTree_h
#define ntp_Lambda_MixTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class ntp_Lambda_MixTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           Lambda_Number;
   Int_t           CounterPart_Number;
   Int_t           Start_Index[6];   //[Lambda_Number]
   Int_t           End_Index[6];   //[Lambda_Number]
   Int_t           CounterPart_FileIndex[1];   //[CounterPart_Number]
   Int_t           CounterPart_EventIndex[1];   //[CounterPart_Number]

   // List of branches
   TBranch        *b_Lambda_Number;   //!
   TBranch        *b_CounterPart_Number;   //!
   TBranch        *b_Start_Index;   //!
   TBranch        *b_End_Index;   //!
   TBranch        *b_CounterPart_FileIndex;   //!
   TBranch        *b_CounterPart_EventIndex;   //!

   ntp_Lambda_MixTree(TTree *tree=0);
   virtual ~ntp_Lambda_MixTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual bool     Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ntp_Lambda_MixTree_cxx
ntp_Lambda_MixTree::ntp_Lambda_MixTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MixTree.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("MixTree.root");
      }
      f->GetObject("ntp_Lambda_MixTree",tree);

   }
   Init(tree);
}

ntp_Lambda_MixTree::~ntp_Lambda_MixTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ntp_Lambda_MixTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ntp_Lambda_MixTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ntp_Lambda_MixTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Lambda_Number", &Lambda_Number, &b_Lambda_Number);
   fChain->SetBranchAddress("CounterPart_Number", &CounterPart_Number, &b_CounterPart_Number);
   fChain->SetBranchAddress("Start_Index", Start_Index, &b_Start_Index);
   fChain->SetBranchAddress("End_Index", End_Index, &b_End_Index);
   fChain->SetBranchAddress("CounterPart_FileIndex", &CounterPart_FileIndex, &b_CounterPart_FileIndex);
   fChain->SetBranchAddress("CounterPart_EventIndex", &CounterPart_EventIndex, &b_CounterPart_EventIndex);
   Notify();
}

bool ntp_Lambda_MixTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return true;
}

void ntp_Lambda_MixTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ntp_Lambda_MixTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ntp_Lambda_MixTree_cxx
