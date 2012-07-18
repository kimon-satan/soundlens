
/*
 *  sieve.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 16/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "sieve.h"

sieve::sieve(){
	
	name = "sieve";
	
		
	dataElement <float> toll;
	toll.name = "tollerance";
	toll.set(0,1,SET_USER_A);
	toll.incr = 0.05;
	floatParameters.push_back(toll);
	
	dataElement <float> offset;
	offset.name = "offset";
	offset.set(0,12,SET_USER_B);
	offset.incr = 1.0;
	floatParameters.push_back(offset);
		
	
	isSample = false;
	
	
	
}


vector<ofPtr<chime> > sieve::getChimes(searchData& sd, ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup){
	
	
	vector<ofPtr<chime> > tmp;
	
	vector<ofPtr<chime> >::iterator it;

	tuningEngine::setOffset(floatParameters[1].abs_val);
	
	for(it = searchGroup.begin(); it != searchGroup.end(); it++){
		
		bool isValid = tuningEngine::checkForMatch((*it)->getFixedParam(CH_FREQ), floatParameters[0].abs_val);
		
		if(isValid){
			tmp.push_back(*it);
			(*it)->setIsTmpSelected(true);
		}else{
			(*it)->setIsTmpSelected(false);
		}	
		
		
	}
	
	return tmp;
	
}





void sieve::drawPreview(float dragDist, float dragAngle){
	
	float d = 0.5 + dragDist * 3.0f;
	
	ofNoFill();
	ofSetColor(150);
	ofCircle(mDown,d);
	
}