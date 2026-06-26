#ifndef ntp_Lambda_LambdaSelecter_h
#define ntp_Lambda_LambdaSelecter_h
#include "constants.h"
#include "TMath.h"

class ntp_Lambda_LambdaSelecter{
public:
	//member variables
	//select pion pt, proton pt, Lambda pt 
	//select pion eta, proton eta, Lambda y 
	//select lambda mass 
	//select lambda decayL 
	//select lambda charge
	//select lamdbda DCAdaughters 
	//select lambda theta
	//select lambda DCA 
	double trackPtMin; 
	double trackPtMax;
	double trackEtaMax;
	double LambdaPtMin;
	double LambdaPtMax;
	double LambdaRapidityMax;
	double LambdaMassMin;
	double LambdaMassMax;
	double LambdaCosThetaMin;
	double LambdaCosThetaMax;
	double LambdaDecayLMin;
	double LambdaDecayLMax;
	double LambdaDauDCAMin;
	double LambdaDauDCAMax;
	double LambdaDCAMin;
	double LambdaDCAMax;

	double PtDiffMax;
	double RapidityDiffMax;
	double PhiDiffMax;



	ntp_Lambda_LambdaSelecter();
	~ntp_Lambda_LambdaSelecter();



	bool IsGoodLambdaMass(double Pt, double Mass);
	bool IsGoodLambda(double pion_Pt,double proton_Pt, double pion_Eta, double proton_Eta, double Lambda_Pt, double Lambda_Rapidity, double Lambda_Mass,double Lambda_DecayL, double Lambda_Theta,double Lambda_DauDCA);
	bool IsGoodLambdaCharge(int Lambda_Charge);
	bool IsGoodLambdaDCA(double Lambda_DecayL,double Lambda_Theta);
	bool IsGoodLambdaCounterpart(double Pt1, double Pt2, double Rapidity1, double Rapidity2, double Phi1, double Phi2,int Charge1, int Chagre2,int proton_Charge1,int proton_Charge2);


};










ntp_Lambda_LambdaSelecter::ntp_Lambda_LambdaSelecter()
{

	trackPtMin  = 0.15;   //GeV/c
	trackPtMax  = 10000.; //GeV/c
	trackEtaMax = 1.0;  //1.5;
	LambdaPtMin = 0.5;  //GeV/c
	LambdaPtMax = 5.0;  //GeV/c
	LambdaRapidityMax =1.0; //1.5;
	LambdaMassMin = Lambda_mass_lowCut;//1.110;//1.10;  //GeV/c62
	LambdaMassMax = Lambda_mass_highCut;//1.122;//1.13;  //GeV/c^2
	LambdaCosThetaMin = 0.996;
	LambdaCosThetaMax = 100.;
	LambdaDecayLMin = 2. ; //cm
	LambdaDecayLMax = 25.; //cm
	LambdaDauDCAMin = -1.; //cm
	LambdaDauDCAMax = 1.0; //cm
	LambdaDCAMin = -1;  //cm
	LambdaDCAMax = 1.0; //cm 


	PtDiffMax = 0.1;
	RapidityDiffMax = 0.1;
	PhiDiffMax = 0.1;


}

ntp_Lambda_LambdaSelecter::~ntp_Lambda_LambdaSelecter(){

}



bool ntp_Lambda_LambdaSelecter::IsGoodLambdaMass(double Pt, double Mass){
	double mean = 1;
	double signa = 100;


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






}

bool ntp_Lambda_LambdaSelecter::IsGoodLambda(double pion_Pt,double proton_Pt, double pion_Eta, double proton_Eta, double Lambda_Pt, double Lambda_Rapidity, double Lambda_Mass, double Lambda_DecayL, double Lambda_Theta,double Lambda_DauDCA)
{
	bool goodness = true;
	if(pion_Pt < trackPtMin || proton_Pt < trackPtMin ) goodness = false;
	if(pion_Eta < (-trackEtaMax) || pion_Eta > trackEtaMax || proton_Eta <(-trackEtaMax) || proton_Eta >trackEtaMax ) goodness = false;
	if(Lambda_Pt < LambdaPtMin  || Lambda_Pt > LambdaPtMax ||  Lambda_Rapidity < (-LambdaRapidityMax) || Lambda_Rapidity > LambdaRapidityMax ) goodness = false;
	//if(Lambda_Mass < LambdaMassMin || Lambda_Mass > LambdaMassMax  ) goodness = false;
	if( ! IsGoodLambdaMass(Lambda_Pt,Lambda_Mass) ) goodness = false;
	if(Lambda_DecayL < LambdaDecayLMin || Lambda_DecayL > LambdaDecayLMax ) goodness = false;
	if(TMath::Cos(Lambda_Theta) < LambdaCosThetaMin ) goodness = false;
	if(Lambda_DauDCA > LambdaDauDCAMax ) goodness = false;

	return goodness;


}

bool ntp_Lambda_LambdaSelecter::IsGoodLambdaCharge(int Lambda_Charge){
	if(Lambda_Charge ==0 ) return true;
	else return false;
}



bool ntp_Lambda_LambdaSelecter::IsGoodLambdaDCA(double Lambda_DecayL,double Lambda_Theta){
	double LambdaDCA = Lambda_DecayL * TMath::Sin(Lambda_Theta);
	if(LambdaDCA < LambdaDCAMax ) return true;
	else return false;
}


bool ntp_Lambda_LambdaSelecter::IsGoodLambdaCounterpart(double Pt1, double Pt2, double Rapidity1, double Rapidity2, double Phi1, double Phi2,int Charge1, int Chagre2,int proton_Charge1,int proton_Charge2){
	bool goodness = true;
	if( TMath::Abs(Pt1-Pt2) > PtDiffMax ) goodness = false;
	if( TMath::Abs(Rapidity1-Rapidity2) > RapidityDiffMax ) goodness = false;
	if( TMath::ACos(TMath::Cos(Phi1-Phi2) ) > PhiDiffMax) goodness = false;
	if(Charge1 != Chagre2) goodness = false;
	if(proton_Charge1!=proton_Charge2) goodness = false;
	return goodness;

}




#endif
