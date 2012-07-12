/*
 *  predefMatchSearch.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 09/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "predefMatchSearch.h"

predefMatchSearch::predefMatchSearch(int param){
	
	isMDrag = true;
	
	name = "match_" + intParameters[0].displayNames[param];
	
	// now don't need these
	floatParameters.clear();
	intParameters.clear();
	
	//get the correct mTolIndex and mTol values
	
	float tolls[7] = {0.1, 0, 0.5, 6, 0.5}; 
	
	mTolIndex = param;
	mTol = tolls[param];
	if(mTolIndex == 0)mTol *= b2_pi;
	
	
	
}


void predefMatchSearch::drawPreview(float dragDist, float dragAngle){

	//matchSearch method
	//nothing to draw here

}

string predefMatchSearch::setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub){

	//override the matchSearch method
	return baseSearch::setUserData(mD,mDr,ua,ub);

}