/*
 *  baseCopy.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 18/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "baseCopy.h"

string baseCopy::setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub){
	
	string s = "";
	
	for(vector<dataElement<int> >::iterator it = intParameters.begin(); it != intParameters.end(); it++){
		
		if(it->isActive){
			s += it->setUserValues(ua,ub,mD);
		}
	}
	
	for(vector<dataElement<float> >::iterator it = floatParameters.begin(); it != floatParameters.end(); it++){
		
		if(it->isActive){
			s += it->setUserValues(ua,ub,mD);
		}
	}
	
	
	mDown.set(mD);
	mDrag.set(mDr);
	
	if(s != "")s = name + ": " + s;
	
	userDataString = s;
	
	return s;
	
}