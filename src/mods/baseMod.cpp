/*
 *  baseMod.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "baseMod.h"

string baseMod::setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub){
	
	string s = "";
	
	for(vector<dataElement<int> >::iterator it = intParameters.begin(); it != intParameters.end(); it++){
		
		if(it->isActive){
			s += it->setUserValues(ua,ub);
			s += "\n";
		}else{
			
		}
	}
	
	for(vector<dataElement<float> >::iterator it = floatParameters.begin(); it != floatParameters.end(); it++){
		
		if(it->isActive){
			s += it->setUserValues(ua,ub);
			s += "\n";
		}
	}
	

	mDown.set(mD);
	mDrag.set(mDr);
	
	if(s != "")s = name + ": \n" + s;
	
	userDataString = s;
	
	return s;
	
}

void baseMod::setName(string s){
	
	name = s;
	
}

string baseMod::getName(){
	
	return name;
	
}
