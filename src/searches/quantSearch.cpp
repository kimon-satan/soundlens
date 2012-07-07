/*
 *  quantSearch.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "quantSearch.h"

quantSearch::quantSearch(){
	
	dataElement <int> po;
	po.name = "offset";
	po.set(0,20,SET_USER_B);
	intParameters.push_back(po);

	dataElement <int> pm;
	pm.name = "mul";
	pm.set(1,20,SET_USER_A);
	intParameters.push_back(pm);
	
	name = "quantOffset";
	
	
}

vector<ofPtr<chime> > quantSearch::getChimes(searchData& sd, ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup){
	
	vector<ofPtr<chime> > tmp;
	
	float tol = sd.phaseTol;
	float angle = 2 * b2_pi/sd.phaseFund;
	float offset = sample->getModParam(CH_PHASE) + (float)intParameters[0].abs_val * angle;
	angle *= intParameters[1].abs_val;
	
	for(vector<ofPtr<chime> >::iterator it = searchGroup.begin(); it != searchGroup.end(); it++){
		
		float rmdr = abs(fmod((*it)->getModParam(CH_PHASE) - offset,angle));
		if(rmdr <= tol || angle - rmdr <= tol){
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