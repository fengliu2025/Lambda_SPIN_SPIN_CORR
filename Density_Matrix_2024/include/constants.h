#ifndef constants_h
#define constants_h


//cut on the track 
const float Track_Pt_LowCut = 0.15;
const float Track_Eta_Cut   = 1.5;


//cut on the lambda 
const float Lambda_Rapidity_Cut = 1.0;
const float Lambda_Pt_lowCut    = 0.5; //GeV/c
const float Lambda_Pt_highCut   = 5.0; //GeV/c
const float Lambda_mass_lowCut  = 1.105;//1.1130060;//1.112250;//1.1135;//GeV/c^2
const float Lambda_mass_highCut = 1.13;//1.1183980;//1.119833;//1.1180;//GeV/c^2


//MixEvent Limitation 
const float ptDiffLim = 0.02;
const float phiDiffLim = 0.02;
const float rapidityDiffLim = 0.02;




//track number bin 
// NTrks_Low<= * <= NTrks_High
const int NTrks_Bin = 3 ;
const int NTrks_Low[NTrks_Bin]  = {0 , 11   , 0 };
const int NTrks_High[NTrks_Bin] = {10 , 100 , 100  };


const int Range_Bin = 5; 
const double Range_Low[Range_Bin]  = {0.  , 0.5 , 1.0, 1.5 , 2.0};
const double Range_High[Range_Bin] = {0.5 , 1.0 , 1.5, 2.0 , 5.0};

//physics constants 
double MASS_PROTON = 0.93827208816;//GeV/c^2
double MASS_PION   = 0.13957039;   //GeV/c^2
#endif
