/*
 *  baseFundSearch.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "baseFundSearch.h"

baseFundSearch::baseFundSearch(){
	
	dataElement <int> p;
	p.name = "fundamental";
	p.set(1,50,SET_USER_B);
	intParameters.push_back(p);
	
	dataElement <int> t;
	t.name = "tollerance";
	t.set(0,20,SET_USER_A);
	intParameters.push_back(t);
	name  = "phaseFundamental";
	
	isSample = true;
	
}

vector<ofPtr<chime> > baseFundSearch::getChimes(searchData& sd, ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup){

	float tol_r = intParameters[1].abs_val * b2_pi/180.0f;
	tol_r = max(tol_r, 0.0001f);
	float angle = 2.0f * b2_pi/(float)intParameters[0].abs_val;
	sd.phaseTol = tol_r;
	
	vector<ofPtr<chime> > tmp;
	
	for(vector<ofPtr<chime> >::iterator it = searchGroup.begin(); it != searchGroup.end(); it++){
		
		float rmdr = fmod((*it)->getModParam(CH_PHASE) - sample->getModParam(CH_PHASE),angle);
		
		if(rmdr <= tol_r || angle - rmdr <= tol_r){
			tmp.push_back(*it);
			(*it)->setIsTmpSelected(true);
		}else{
			(*it)->setIsTmpSelected(false);
		}	
	}
	
	sd.phaseFund = intParameters[0].abs_val;
	
	return tmp;
	
}

void baseFundSearch::drawPreview(float dragDist, float dragAngle){
	
	//may end up as a method in baseSearch for reuse
	
	float d = 0.5 + intParameters[1].abs_val * 3.0f/(float)intParameters[1].max_val;
	
	ofNoFill();
	ofSetColor(150);
	ofCircle(mDown,d);
	ofVec2f p(mDown + ofVec2f(0,d));
	p.rotate(-intParameters[0].abs_val * 360/intParameters[0].max_val,mDown);
	ofLine(mDown.x, mDown.y, p.x, p.y);
	
	
}