#ifndef ntp_K0s_K0sSelecter_h
#define ntp_K0s_K0sSelecter_h
#include "constants.h"
#include "TMath.h"

class ntp_K0s_K0sSelecter{
public:
	//member variables
	//select pion pt, pion2 pt, K0s pt 
	//select pion eta, pion2 eta, K0s y 
	//select K0s mass 
	//select K0s decayL 
	//select K0s charge
	//select lamdbda DCAdaughters 
	//select K0s theta
	//select K0s DCA 
	double trackPtMin; 
	double trackPtMax;
	double trackEtaMax;
	double K0sPtMin;
	double K0sPtMax;
	double K0sRapidityMax;
	double K0sMassMin;
	double K0sMassMax;
	double K0sCosThetaMin;
	double K0sCosThetaMax;
	double K0sDecayLMin;
	double K0sDecayLMax;
	double K0sDauDCAMin;
	double K0sDauDCAMax;
	double K0sDCAMin;
	double K0sDCAMax;

	double PtDiffMax;
	double RapidityDiffMax;
	double PhiDiffMax;

	double pion_DCAMin;



	ntp_K0s_K0sSelecter();
	~ntp_K0s_K0sSelecter();


	bool IsGoodDauDCA(double pion_DCA, double pion2_DCA);
	bool IsGoodK0sMass(double Pt, double Mass);
	bool IsGoodK0s(double pion_Pt,double pion2_Pt, double pion_Eta, double pion2_Eta, double K0s_Pt, double K0s_Rapidity, double K0s_Mass,double K0s_DecayL, double K0s_Theta,double K0s_DauDCA);
	bool IsGoodK0sCharge(int K0s_Charge);
	bool IsGoodK0sDCA(double K0s_DecayL,double K0s_Theta);
	bool IsGoodK0sCounterpart(double Pt1, double Pt2, double Rapidity1, double Rapidity2, double Phi1, double Phi2,int Charge1, int Chagre2);


};










ntp_K0s_K0sSelecter::ntp_K0s_K0sSelecter()
{

	trackPtMin  = 0.15;   //GeV/c
	trackPtMax  = 10000.; //GeV/c
	trackEtaMax = 1.5;  //1.5;
	K0sPtMin = 0.5;  //GeV/c
	K0sPtMax = 5.0;  //GeV/c
	K0sRapidityMax =1.0; //1.5;
	K0sMassMin = 0.45;//K0s_mass_lowCut;//1.110;//1.10;  //GeV/c62
	K0sMassMax = 0.55;//K0s_mass_highCut;//1.122;//1.13;  //GeV/c^2
	K0sCosThetaMin = 0.996;
	K0sCosThetaMax = 100.;
	K0sDecayLMin = 0.5 ; //cm
	K0sDecayLMax = 25.; //cm
	K0sDauDCAMin = -1.; //cm
	K0sDauDCAMax = 1.0; //cm
	K0sDCAMin = -1;  //cm
	K0sDCAMax = 1.0; //cm 

	
	pion_DCAMin = 0.3; //cm;


	PtDiffMax = 0.1;
	RapidityDiffMax = 0.1;
	PhiDiffMax = 0.1;


}

ntp_K0s_K0sSelecter::~ntp_K0s_K0sSelecter(){

}



bool ntp_K0s_K0sSelecter::IsGoodDauDCA(double pion_DCA,double pion2_DCA){
	bool goodness = true;
	if(pion_DCA < pion_DCAMin) goodness= false;
	if(pion2_DCA < pion_DCAMin ) goodness = false;
	return goodness;

}

bool ntp_K0s_K0sSelecter::IsGoodK0sMass(double Pt, double Mass){
	/*double mean = 1;
	double sigma = 100;


	if(Pt < 1.5){
		mean = 1.115702;
		sigma = 0.00134;
	}

	else {
		mean = 1.115765;
		sigma = 0.001915; 
	}

	if( Mass > (mean -2 *sigma )  && Mass < (mean + 2*sigma) ){
		return true;
	}

	else return false;
	*/
	return false;
}

bool ntp_K0s_K0sSelecter::IsGoodK0s(double pion_Pt,double pion2_Pt, double pion_Eta, double pion2_Eta, double K0s_Pt, double K0s_Rapidity, double K0s_Mass, double K0s_DecayL, double K0s_Theta,double K0s_DauDCA)
{
	bool goodness = true;
	if(pion_Pt < trackPtMin || pion2_Pt < trackPtMin ) goodness = false;
	if(pion_Eta < (-trackEtaMax) || pion_Eta > trackEtaMax || pion2_Eta <(-trackEtaMax) || pion2_Eta >trackEtaMax ) goodness = false;
	if(K0s_Pt < K0sPtMin  || K0s_Pt > K0sPtMax ||  K0s_Rapidity < (-K0sRapidityMax) || K0s_Rapidity > K0sRapidityMax ) goodness = false;
	if(K0s_Mass < K0sMassMin || K0s_Mass > K0sMassMax  ) goodness = false;
	//if( ! IsGoodK0sMass(K0s_Pt,K0s_Mass) ) goodness = false;
	if(K0s_DecayL < K0sDecayLMin || K0s_DecayL > K0sDecayLMax ) goodness = false;
	if(TMath::Cos(K0s_Theta) < K0sCosThetaMin ) goodness = false;
	if(K0s_DauDCA > K0sDauDCAMax ) goodness = false;

	return goodness;


}

bool ntp_K0s_K0sSelecter::IsGoodK0sCharge(int K0s_Charge){
	if(K0s_Charge ==0 ) return true;
	else return false;
}



bool ntp_K0s_K0sSelecter::IsGoodK0sDCA(double K0s_DecayL,double K0s_Theta){
	double K0sDCA = K0s_DecayL * TMath::Sin(K0s_Theta);
	if(K0sDCA < K0sDCAMax ) return true;
	else return false;
}


bool ntp_K0s_K0sSelecter::IsGoodK0sCounterpart(double Pt1, double Pt2, double Rapidity1, double Rapidity2, double Phi1, double Phi2,int Charge1, int Chagre2){
	bool goodness = true;
	if( TMath::Abs(Pt1-Pt2) > PtDiffMax ) goodness = false;
	if( TMath::Abs(Rapidity1-Rapidity2) > RapidityDiffMax ) goodness = false;
	if( TMath::ACos(TMath::Cos(Phi1-Phi2) ) > PhiDiffMax) goodness = false;
	if(Charge1 != Chagre2) goodness = false;
	return goodness;

}




#endif
