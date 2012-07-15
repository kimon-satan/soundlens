/*
 *  fundSearch.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 09/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "fundSearch.h"

fundSearch::fundSearch(int fType){
	
	isSample = true;
	isMDrag = false;
	
	int params[] = {CH_PHASE, CH_SPEED, CH_FREQ};
	
	fundType = params[fType];
	
	dataElement <float> fundParam;
	fundParam.name = "fund";
	
	dataElement <float> tolParam;
	tolParam.name = "toll";
	
	if(fundType == CH_PHASE){
	
		name  = "phaseFund";
		fundParam.incr = 1.0;
		fundParam.set(1,50,SET_USER_B);
		tolParam.incr = 1.0;
		tolParam.set(0,20,SET_USER_A);
		
		
	}else if(fundType == CH_SPEED){
		
		name  = "speedFund";
		fundParam.incr = 0.01;
		fundParam.set(0.01,0.25,SET_USER_B);
		tolParam.incr = 0.01;
		tolParam.set(0,1.0,SET_USER_A);
	
	
	}else if(fundType == CH_FREQ){
		
		name  = "freqFund";
		fundParam.incr = 0.01;
		fundParam.set(0.25,6,SET_USER_B);
		tolParam.incr = 0.01;
		tolParam.set(0,1.0,SET_USER_A);
	
	}
	
	floatParameters.push_back(fundParam);
	floatParameters.push_back(tolParam);

	
}

vector<ofPtr<chime> > fundSearch::getChimes(searchData& sd, ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup){
	
	float tol_r = (fundType == CH_PHASE) ? floatParameters[1].abs_val * b2_pi/180.0f : floatParameters[1].abs_val;
	tol_r = max(tol_r, 0.0001f);
	
	float div = (fundType == CH_PHASE) ? 2.0f * b2_pi/floatParameters[0].abs_val : floatParameters[0].abs_val;
	
	
	vector<ofPtr<chime> > tmp;
	
	for(vector<ofPtr<chime> >::iterator it = searchGroup.begin(); it != searchGroup.end(); it++){
		
		bool isFund = false;
			
			float rmdr = (*it)->getFixedParam(fundType) - sample->getFixedParam(fundType);
			rmdr = fmod(abs(rmdr),div);
			
			if(rmdr <= tol_r || div - rmdr <= tol_r)isFund = true;
			
			
		if(isFund){
			tmp.push_back(*it);
			(*it)->setIsTmpSelected(true);
		}else{
			(*it)->setIsTmpSelected(false);
		}	
	}
	
	
	switch (fundType) {
		
		case CH_PHASE:
			sd.phaseTol = tol_r;
			sd.phaseFund = div;
			break;
		case CH_SPEED:
			sd.speedTol = tol_r;
			sd.speedFund = div;
			break;
		case CH_FREQ:
			sd.freqTol = tol_r;
			sd.freqFund = div;
			break;

	};

	
	return tmp;
	
}

void fundSearch::drawPreview(float dragDist, float dragAngle){
	
	//may end up as a method in baseSearch for reuse
	
	float d = 0.5 + floatParameters[1].abs_val * 3.0f/(float)floatParameters[1].max_val;
	
	ofNoFill();
	ofSetColor(150);
	ofCircle(mDown,d);
	ofVec2f p(mDown + ofVec2f(0,d));
	p.rotate(-floatParameters[0].abs_val * 360/floatParameters[0].max_val,mDown);
	ofLine(mDown.x, mDown.y, p.x, p.y);
	
	
}