
#ifndef ntp_Lambda_Reader_h
#define ntp_Lambda_Reader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class ntp_Lambda_Reader {
public :
   std::vector<std::string> InputFiles;
   std::vector<std::vector<std::string> > InputFiles_MixEvent;

   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           eventId;
   Float_t         Vz;
   Int_t           mNTrigs;
   Int_t           mTrigId[5];   //[mNTrigs]
   Int_t           mNTrks;
   Float_t         high_pt[50];   //[mNTrks]
   Float_t         high_phi[50];   //[mNTrks]
   Float_t         high_eta[50];   //[mNTrks]
   Int_t           NLambda;
   Int_t           p1_InEventID[50];   //[NLambda]
   Float_t         p1_pt[50];   //[NLambda]
   Float_t         p1_phi[50];   //[NLambda]
   Float_t         p1_eta[50];   //[NLambda]
   Float_t         p1_dca[50];   //[NLambda]
   Int_t           p1_ch[50];   //[NLambda]
   Int_t           p1_hasTOFinfo[50];   //[NLambda]
   Float_t         p1_dedx[50];   //[NLambda]
   Float_t         p1_beta[50];   //[NLambda]
   Float_t         p1_dcaxy[8];   //[NLambda]
   Float_t         p1_nSigmaProton[8];   //[NLambda]
   Int_t           p2_InEventID[50];   //[NLambda]
   Float_t         p2_pt[50];   //[NLambda]
   Float_t         p2_phi[50];   //[NLambda]
   Float_t         p2_eta[50];   //[NLambda]
   Float_t         p2_dca[50];   //[NLambda]
   Float_t         p2_ch[50];   //[NLambda]
   Int_t           p2_hasTOFinfo[50];   //[NLambda]
   Float_t         p2_dedx[50];   //[NLambda]
   Float_t         p2_beta[50];   //[NLambda]
   Float_t         p2_dcaxy[8];   //[NLambda]
   Float_t         p2_nSigmaPion[8];   //[NLambda]
   Int_t           pair_charge[50];   //[NLambda]
   Float_t         pair_DCAdaughters[50];   //[NLambda]
   Float_t         pair_theta[50];   //[NLambda]
   Float_t         pair_decayL[50];   //[NLambda]
   Float_t         pair_phi[50];   //[NLambda]
   Float_t         pair_eta[50];   //[NLambda]
   Float_t         pair_pt[50];   //[NLambda]
   Float_t         pair_mass[50];   //[NLambda]
   Int_t           track_Number;
   Float_t         track_pt[1000];   //[track_Number]
   Float_t         track_eta[1000];   //[track_Number]
   Float_t         track_phi[1000];   //[track_Number]
   Int_t           track_InEventID[1000];   //[track_Number]
   Float_t         track_dca[1000];   //[track_Number]
   Float_t         track_dcaxy[1000];   //[track_Number]
   Float_t         track_nSigmaPion[1000];   //[track_Number]
   Float_t         track_nSigmaKaon[1000];   //[track_Number]
   Float_t         track_nSigmaProton[1000];   //[track_Number]
   Float_t         track_dedx[1000];   //[track_Number]
   Int_t           track_ch[1000];   //[track_Number]


   // List of branches
   TBranch        *b_eventId;   //!
   TBranch        *b_Vz;   //!
   TBranch        *b_mNTrigs;   //!
   TBranch        *b_mTrigId;   //!
   TBranch        *b_mNTrks;   //!
   TBranch        *b_high_pt;   //!
   TBranch        *b_high_phi;   //!
   TBranch        *b_high_eta;   //!
   TBranch        *b_NLambda;   //!
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
   TBranch        *b_p1_nSigmaProton;   //!
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

   ntp_Lambda_Reader(std::vector<std::string> Infiles);
   ntp_Lambda_Reader(std::vector<std::vector<std::string>> Infiles);
   virtual ~ntp_Lambda_Reader();
   virtual void     Init(TTree *tree);
};



ntp_Lambda_Reader::ntp_Lambda_Reader(std::vector<std::string> Infiles) 
   : fChain(0), InputFiles(Infiles)
{

}

ntp_Lambda_Reader::ntp_Lambda_Reader(std::vector<std::vector<std::string>> Infiles) 
   : fChain(0), InputFiles_MixEvent(Infiles)
{

}


ntp_Lambda_Reader::~ntp_Lambda_Reader()
{
   
}



void ntp_Lambda_Reader::Init(TTree *tree)
{

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
   fChain->SetBranchAddress("NLambda", &NLambda, &b_NLambda);
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
   fChain->SetBranchAddress("p1_nSigmaProton", p1_nSigmaProton, &b_p1_nSigmaProton);
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
   
   /* 
   fChain->SetBranchStatus("track_Number", 0);
   fChain->SetBranchStatus("track_pt", 0);
   fChain->SetBranchStatus("track_eta", 0);
   fChain->SetBranchStatus("track_phi", 0);
   fChain->SetBranchStatus("track_InEventID", 0);
   fChain->SetBranchStatus("track_dca", 0);
   fChain->SetBranchStatus("track_dcaxy", 0);
   fChain->SetBranchStatus("track_nSigmaPion", 0);
   fChain->SetBranchStatus("track_nSigmaKaon", 0);
   fChain->SetBranchStatus("track_nSigmaProton", 0);
   fChain->SetBranchStatus("track_dedx", 0);
   fChain->SetBranchStatus("track_ch", 0);   
   */
}

#endif


