/*
 *  quantSearch.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "quantSearch.h"

quantSearch::quantSearch(int fType){
	
	dataElement <int> offset;
	dataElement <int> mul;
	offset.name = "offset";
	mul.name = "mul";
	offset.set(0,20,SET_USER_B);
	mul.set(1,20,SET_USER_A);
	
	int params[] = {CH_PHASE, CH_SPEED, CH_FREQ};
	
	fundType = params[fType];
	

	switch(fundType){
	
		case CH_FREQ:
			name = "Quant_freq";
			break;
		case CH_PHASE:
			name = "Quant_phase";
			break;
		case CH_SPEED:
			name = "Quant_speed";
			break;
			
	}
	
	intParameters.push_back(offset);
	intParameters.push_back(mul);
	
	isMDrag = false;
	isSample = true;
	
}

vector<ofPtr<chime> > quantSearch::getChimes(searchData& sd, ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup){
	
	vector<ofPtr<chime> > tmp;
	
	float tol, div;
	
	switch(fundType){
			
		case CH_FREQ:
			tol = sd.freqTol;
			div = sd.freqFund;
			break;
		case CH_PHASE:
			tol = sd.phaseTol;
			div = sd.phaseFund;
			break;
		case CH_SPEED:
			tol = sd.speedTol;
			div = sd.speedFund;
			break;
	}
	
	
	float offset = sample->getFixedParam(fundType) + (float)intParameters[0].abs_val * div;
	div *= intParameters[1].abs_val;
	
	for(vector<ofPtr<chime> >::iterator it = searchGroup.begin(); it != searchGroup.end(); it++){
		
		bool isQuant = true;
		
		float rmdr = abs(fmod((*it)->getFixedParam(fundType) - offset,div));
		rmdr = min(rmdr, div - rmdr);
		if(rmdr > tol)isQuant = false;
		
		if(isQuant){
			tmp.push_back(*it);
			(*it)->setIsTmpSelected(true);
		}else{
			(*it)->setIsTmpSelected(false);
		}	
	}
	
	
	return tmp;
	
}


void quantSearch::drawPreview(float dragDist, float dragAngle){
	
	//not decided yet
	float d = 0.5 + intParameters[1].abs_val * 3.0f/(float)intParameters[1].max_val;
	
	ofNoFill();
	ofSetColor(150);
	ofCircle(mDown,d);
	ofVec2f p(mDown + ofVec2f(0,d));
	p.rotate(-intParameters[0].abs_val * 360/intParameters[0].max_val,mDown);
	ofLine(mDown.x, mDown.y, p.x, p.y);
	
	
}