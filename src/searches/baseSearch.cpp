/*
 *  baseSearch.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "baseSearch.h"

string baseSearch::setUserData(float ua, float ub){

	string s = "";
	
	for(vector<dataElement<float> >::iterator it = floatParameters.begin(); it != floatParameters.end(); it++){
		
		s += it->setUserValues(ua,ub);
	}
	
	for(vector<dataElement<int> >::iterator it = intParameters.begin(); it != intParameters.end(); it++){
		
		s += it->setUserValues(ua,ub);
	}
	
	/*for(vector<dataElement<ofVec2f> >::iterator it = vecParameters.begin(); it != vecParameters.end(); it++){
		
		s += it->setUserValues(ua,ub);
	}*/
	
	if(s != "")s = name + ": " + s;
	
	userDataString = s;
	
	return s;
	
}

void baseSearch::setName(string s){

	name = s;
	
}