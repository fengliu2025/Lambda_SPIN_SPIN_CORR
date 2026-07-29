#ifndef ntp_K0s_EventSelecter_h
#define ntp_K0s_EventSelecter_h

class ntp_K0s_EventSelecter{
public:
	//member variables 
	std::vector<int> AllowedTriggerId;
	std::vector<int> NotAllowedTriggerId;
	Float_t VzMax;
	//memeber functions

	ntp_K0s_EventSelecter();
	virtual ~ntp_K0s_EventSelecter();


	bool IsGoodEvent(std::vector<int> EventTrigId);
	bool IsGoodEvent(float Vz);
	bool IsGoodEvent();


};


ntp_K0s_EventSelecter::ntp_K0s_EventSelecter()
	: VzMax(60)
{

}

ntp_K0s_EventSelecter::~ntp_K0s_EventSelecter(){

}


 bool ntp_K0s_EventSelecter::IsGoodEvent(std::vector<int> EventTrigId){
 	bool goodness = false;
 	
 	for(int i=0 ; i < EventTrigId.size();i++){
 		for(int j=0; j< AllowedTriggerId.size();j++){
 			if( EventTrigId[i] == AllowedTriggerId[j] ) goodness = true;
 		}
 	}

	for(int i=0; i < EventTrigId.size();i++){
 		for(int j=0; j < NotAllowedTriggerId.size();j++){
 			if(EventTrigId[i] == NotAllowedTriggerId[j] ) goodness = false;
 		}
 	}

 	return goodness;

 }

 bool ntp_K0s_EventSelecter::IsGoodEvent(float Vz){
 	if( Vz < VzMax && Vz >(-VzMax) ) return true;
 	else return false;
 }





 bool ntp_K0s_EventSelecter::IsGoodEvent(){
 	return true;
 }







#endif
