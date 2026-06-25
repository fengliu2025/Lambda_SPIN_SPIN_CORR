#ifndef constants_h
#define constants_h

const int Range_Bin = 2; 
//cut on the track 
const float Track_Pt_LowCut = 0.15;
const float Track_Eta_Cut   = 1.5;


//cut on the lambda 
const float Lambda_Rapidity_Cut = 1.0;
const float Lambda_Pt_lowCut    = 0.5; //GeV/c
const float Lambda_Pt_highCut   = 5.0; //GeV/c
const float Lambda_mass_lowCut  = 1.110;//GeV/c^2
const float Lambda_mass_highCut = 1.122;//GeV/c^2


//MixEvent Limitation 
const float ptDiffLim = 0.02;
const float phiDiffLim = 0.02;
const float rapidityDiffLim = 0.02;

//physics constants 
double MASS_PROTON = 0.93827208816;//GeV/c^2
double MASS_PION   = 0.13957039;   //GeV/c^2
#endif
