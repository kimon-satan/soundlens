/*
 *  baseSearch.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "baseSearch.h"

string baseSearch::setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub){

	userDataString  = "";
	
	for(vector<dataElement<int> >::iterator it = intParameters.begin(); it != intParameters.end(); it++){
		
		if(it->isActive){
			string s = it->setUserValues(ua,ub);
			if(s != ""){
				s += "\n";
				userDataString += s;
			}
		}
	}
	
	for(vector<dataElement<float> >::iterator it = floatParameters.begin(); it != floatParameters.end(); it++){
		
		if(it->isActive){
			string s = it->setUserValues(ua,ub);
			if(s != ""){
				s += "\n";
				userDataString += s;
			}
		}
	}
	
	mDown.set(mD);
	mDrag.set(mDr);
	
	if(userDataString  != "")userDataString  = name + ": \n" + userDataString;
	
	
	return userDataString ;
	
}

void baseSearch::setName(string s){

	name = s;
	
}

string baseSearch::getName(){
	
	return name;

}

bool baseSearch::getIsSample(){
	return isSample;
}

bool baseSearch::getIsMDrag(){
	return isMDrag;
}