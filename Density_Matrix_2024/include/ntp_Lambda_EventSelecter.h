#ifndef ntp_Lambda_EventSelecter_h
#define ntp_Lambda_EventSelecter_h

class ntp_Lambda_EventSelecter{
public:
	//member variables 
	std::vector<int> AllowedTriggerId;
	std::vector<int> NotAllowedTriggerId;
	Float_t VzMax;
	//memeber functions

	ntp_Lambda_EventSelecter();
	virtual ~ntp_Lambda_EventSelecter();


	bool IsGoodEvent(std::vector<int> EventTrigId,float Vz );
	bool IsGoodEvent(float Vz);
	bool IsGoodEvent();


};


ntp_Lambda_EventSelecter::ntp_Lambda_EventSelecter()
	: VzMax(60)
{

}

ntp_Lambda_EventSelecter::~ntp_Lambda_EventSelecter(){

}


 bool ntp_Lambda_EventSelecter::IsGoodEvent(std::vector<int> EventTrigId, float Vz){
 	bool goodness = false;
 	
 	for(int i=0 ; i < EventTrigId.size();i++){
 		for(int j=0; j< AllowedTriggerId.size();j++){
 			if( EventTrigId[i] == AllowedTriggerId[j] ) goodness = true;
 		}
 	}

 	for(int i=0; i < EventTrigId.size();i++){
 		for(int j=0; j < NotAllowedTriggerId.size();j++){
 			if(EventTrigId[i] == AllowedTriggerId[j] ) goodness = false;
 		}
 	}



 	if(Vz > VzMax || Vz < (-VzMax) ) goodness = false;

 	return goodness;

 }

 bool ntp_Lambda_EventSelecter::IsGoodEvent(float Vz){
 	if( Vz < VzMax && Vz >(-VzMax) ) return true;
 	else return false;
 }





 bool ntp_Lambda_EventSelecter::IsGoodEvent(){
 	return true;
 }







#endif
