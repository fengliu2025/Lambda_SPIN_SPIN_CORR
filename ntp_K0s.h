//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jul 27 22:50:14 2026 by ROOT version 5.34/38
// from TTree ntp_K0s/K0s TTree
// found on file: HRun25122005_00picoDstK0s.root.picoLambdaAnaMaker.root
//////////////////////////////////////////////////////////

#ifndef ntp_K0s_h
#define ntp_K0s_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class ntp_K0s {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           eventId;
   Float_t         Vz;
   Int_t           mNTrigs;
   Int_t           mTrigId[2];   //[mNTrigs]
   Int_t           mNTrks;
   Float_t         high_pt[2];   //[mNTrks]
   Float_t         high_phi[2];   //[mNTrks]
   Float_t         high_eta[2];   //[mNTrks]
   Int_t           NK0s;
   Int_t           p1_InEventID[4];   //[NK0s]
   Float_t         p1_pt[4];   //[NK0s]
   Float_t         p1_phi[4];   //[NK0s]
   Float_t         p1_eta[4];   //[NK0s]
   Float_t         p1_dca[4];   //[NK0s]
   Int_t           p1_ch[4];   //[NK0s]
   Int_t           p1_hasTOFinfo[4];   //[NK0s]
   Float_t         p1_dedx[4];   //[NK0s]
   Float_t         p1_beta[4];   //[NK0s]
   Float_t         p1_dcaxy[4];   //[NK0s]
   Float_t         p1_nSigmaPion[4];   //[NK0s]
   Int_t           p2_InEventID[4];   //[NK0s]
   Float_t         p2_pt[4];   //[NK0s]
   Float_t         p2_phi[4];   //[NK0s]
   Float_t         p2_eta[4];   //[NK0s]
   Float_t         p2_dca[4];   //[NK0s]
   Int_t           p2_ch[4];   //[NK0s]
   Int_t           p2_hasTOFinfo[4];   //[NK0s]
   Float_t         p2_dedx[4];   //[NK0s]
   Float_t         p2_beta[4];   //[NK0s]
   Float_t         p2_dcaxy[4];   //[NK0s]
   Float_t         p2_nSigmaPion[4];   //[NK0s]
   Int_t           pair_charge[4];   //[NK0s]
   Float_t         pair_DCAdaughters[4];   //[NK0s]
   Float_t         pair_theta[4];   //[NK0s]
   Float_t         pair_decayL[4];   //[NK0s]
   Float_t         pair_phi[4];   //[NK0s]
   Float_t         pair_eta[4];   //[NK0s]
   Float_t         pair_pt[4];   //[NK0s]
   Float_t         pair_mass[4];   //[NK0s]
   Int_t           track_Number;
   Float_t         track_pt[97];   //[track_Number]
   Float_t         track_eta[97];   //[track_Number]
   Float_t         track_phi[97];   //[track_Number]
   Int_t           track_InEventID[97];   //[track_Number]
   Float_t         track_dca[97];   //[track_Number]
   Float_t         track_dcaxy[97];   //[track_Number]
   Float_t         track_nSigmaPion[97];   //[track_Number]
   Float_t         track_nSigmaKaon[97];   //[track_Number]
   Float_t         track_nSigmaProton[97];   //[track_Number]
   Float_t         track_dedx[97];   //[track_Number]
   Int_t           track_ch[97];   //[track_Number]

   // List of branches
   TBranch        *b_eventId;   //!
   TBranch        *b_Vz;   //!
   TBranch        *b_mNTrigs;   //!
   TBranch        *b_mTrigId;   //!
   TBranch        *b_mNTrks;   //!
   TBranch        *b_high_pt;   //!
   TBranch        *b_high_phi;   //!
   TBranch        *b_high_eta;   //!
   TBranch        *b_NK0s;   //!
   TBranch        *b_p1_InEventID;   //!
   TBranch        *b_p1_pt;   //!
   TBranch        *b_p1_phi;   //!
   TBranch        *b_p1_eta;   //!
   TBranch        *b_p1_dca;   //!
   TBranch        *b_p1_ch;   //!
   TBranch        *b_p1_hasTOFinfo;   //!
   TBranch        *b_p1_dedx;   //!
   TBranch        *b_p1_beta;   //!
   TBranch        *b_p1_dcaxy;   //!
   TBranch        *b_p1_nSigmaPion;   //!
   TBranch        *b_p2_InEventID;   //!
   TBranch        *b_p2_pt;   //!
   TBranch        *b_p2_phi;   //!
   TBranch        *b_p2_eta;   //!
   TBranch        *b_p2_dca;   //!
   TBranch        *b_p2_ch;   //!
   TBranch        *b_p2_hasTOFinfo;   //!
   TBranch        *b_p2_dedx;   //!
   TBranch        *b_p2_beta;   //!
   TBranch        *b_p2_dcaxy;   //!
   TBranch        *b_p2_nSigmaPion;   //!
   TBranch        *b_pair_charge;   //!
   TBranch        *b_pair_DCAdaughters;   //!
   TBranch        *b_pair_theta;   //!
   TBranch        *b_pair_decayL;   //!
   TBranch        *b_pair_phi;   //!
   TBranch        *b_pair_eta;   //!
   TBranch        *b_pair_pt;   //!
   TBranch        *b_pair_mass;   //!
   TBranch        *b_track_Number;   //!
   TBranch        *b_track_pt;   //!
   TBranch        *b_track_eta;   //!
   TBranch        *b_track_phi;   //!
   TBranch        *b_track_InEventID;   //!
   TBranch        *b_track_dca;   //!
   TBranch        *b_track_dcaxy;   //!
   TBranch        *b_track_nSigmaPion;   //!
   TBranch        *b_track_nSigmaKaon;   //!
   TBranch        *b_track_nSigmaProton;   //!
   TBranch        *b_track_dedx;   //!
   TBranch        *b_track_ch;   //!

   ntp_K0s(TTree *tree=0);
   virtual ~ntp_K0s();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ntp_K0s_cxx
ntp_K0s::ntp_K0s(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("HRun25122005_00picoDstK0s.root.picoLambdaAnaMaker.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("HRun25122005_00picoDstK0s.root.picoLambdaAnaMaker.root");
      }
      f->GetObject("ntp_K0s",tree);

   }
   Init(tree);
}

ntp_K0s::~ntp_K0s()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ntp_K0s::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ntp_K0s::LoadTree(Long64_t entry)
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

void ntp_K0s::Init(TTree *tree)
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

   fChain->SetBranchAddress("eventId", &eventId, &b_eventId);
   fChain->SetBranchAddress("Vz", &Vz, &b_Vz);
   fChain->SetBranchAddress("mNTrigs", &mNTrigs, &b_mNTrigs);
   fChain->SetBranchAddress("mTrigId", mTrigId, &b_mTrigId);
   fChain->SetBranchAddress("mNTrks", &mNTrks, &b_mNTrks);
   fChain->SetBranchAddress("high_pt", high_pt, &b_high_pt);
   fChain->SetBranchAddress("high_phi", high_phi, &b_high_phi);
   fChain->SetBranchAddress("high_eta", high_eta, &b_high_eta);
   fChain->SetBranchAddress("NK0s", &NK0s, &b_NK0s);
   fChain->SetBranchAddress("p1_InEventID", p1_InEventID, &b_p1_InEventID);
   fChain->SetBranchAddress("p1_pt", p1_pt, &b_p1_pt);
   fChain->SetBranchAddress("p1_phi", p1_phi, &b_p1_phi);
   fChain->SetBranchAddress("p1_eta", p1_eta, &b_p1_eta);
   fChain->SetBranchAddress("p1_dca", p1_dca, &b_p1_dca);
   fChain->SetBranchAddress("p1_ch", p1_ch, &b_p1_ch);
   fChain->SetBranchAddress("p1_hasTOFinfo", p1_hasTOFinfo, &b_p1_hasTOFinfo);
   fChain->SetBranchAddress("p1_dedx", p1_dedx, &b_p1_dedx);
   fChain->SetBranchAddress("p1_beta", p1_beta, &b_p1_beta);
   fChain->SetBranchAddress("p1_dcaxy", p1_dcaxy, &b_p1_dcaxy);
   fChain->SetBranchAddress("p1_nSigmaPion", p1_nSigmaPion, &b_p1_nSigmaPion);
   fChain->SetBranchAddress("p2_InEventID", p2_InEventID, &b_p2_InEventID);
   fChain->SetBranchAddress("p2_pt", p2_pt, &b_p2_pt);
   fChain->SetBranchAddress("p2_phi", p2_phi, &b_p2_phi);
   fChain->SetBranchAddress("p2_eta", p2_eta, &b_p2_eta);
   fChain->SetBranchAddress("p2_dca", p2_dca, &b_p2_dca);
   fChain->SetBranchAddress("p2_ch", p2_ch, &b_p2_ch);
   fChain->SetBranchAddress("p2_hasTOFinfo", p2_hasTOFinfo, &b_p2_hasTOFinfo);
   fChain->SetBranchAddress("p2_dedx", p2_dedx, &b_p2_dedx);
   fChain->SetBranchAddress("p2_beta", p2_beta, &b_p2_beta);
   fChain->SetBranchAddress("p2_dcaxy", p2_dcaxy, &b_p2_dcaxy);
   fChain->SetBranchAddress("p2_nSigmaPion", p2_nSigmaPion, &b_p2_nSigmaPion);
   fChain->SetBranchAddress("pair_charge", pair_charge, &b_pair_charge);
   fChain->SetBranchAddress("pair_DCAdaughters", pair_DCAdaughters, &b_pair_DCAdaughters);
   fChain->SetBranchAddress("pair_theta", pair_theta, &b_pair_theta);
   fChain->SetBranchAddress("pair_decayL", pair_decayL, &b_pair_decayL);
   fChain->SetBranchAddress("pair_phi", pair_phi, &b_pair_phi);
   fChain->SetBranchAddress("pair_eta", pair_eta, &b_pair_eta);
   fChain->SetBranchAddress("pair_pt", pair_pt, &b_pair_pt);
   fChain->SetBranchAddress("pair_mass", pair_mass, &b_pair_mass);
   fChain->SetBranchAddress("track_Number", &track_Number, &b_track_Number);
   fChain->SetBranchAddress("track_pt", track_pt, &b_track_pt);
   fChain->SetBranchAddress("track_eta", track_eta, &b_track_eta);
   fChain->SetBranchAddress("track_phi", track_phi, &b_track_phi);
   fChain->SetBranchAddress("track_InEventID", track_InEventID, &b_track_InEventID);
   fChain->SetBranchAddress("track_dca", track_dca, &b_track_dca);
   fChain->SetBranchAddress("track_dcaxy", track_dcaxy, &b_track_dcaxy);
   fChain->SetBranchAddress("track_nSigmaPion", track_nSigmaPion, &b_track_nSigmaPion);
   fChain->SetBranchAddress("track_nSigmaKaon", track_nSigmaKaon, &b_track_nSigmaKaon);
   fChain->SetBranchAddress("track_nSigmaProton", track_nSigmaProton, &b_track_nSigmaProton);
   fChain->SetBranchAddress("track_dedx", track_dedx, &b_track_dedx);
   fChain->SetBranchAddress("track_ch", track_ch, &b_track_ch);
   Notify();
}

Bool_t ntp_K0s::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ntp_K0s::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ntp_K0s::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ntp_K0s_cxx
