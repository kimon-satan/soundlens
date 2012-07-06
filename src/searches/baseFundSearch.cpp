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
	
}

vector<ofPtr<chime> > baseFundSearch::getChimes(searchData& sd, ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup){

	float tol_r = intParameters[1].abs_val * b2_pi/180.0f;
	tol_r = max(tol_r, 0.0001f);
	float angle = 2.0f * b2_pi/(float)intParameters[0].abs_val;
	
	vector<ofPtr<chime> > tmp;
	
	for(vector<ofPtr<chime> >::iterator it = searchGroup.begin(); it != searchGroup.end(); it++){
		
		float rmdr = fmod((*it)->getPhase() - sample->getPhase(),angle);
		
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

void baseFundSearch::drawPreview(ofVec2f mouseDownPos, ofVec2f mouseDragPos, float dragDist, float dragAngle){
	
	//may end up as a method in baseSearch for reuse
	
	float d = 0.5 + dragDist * 3;
	
	ofNoFill();
	ofSetColor(150);
	ofCircle(mouseDownPos,d);
	ofVec2f p(mouseDownPos + ofVec2f(0,d));
	p.rotate(dragAngle * 360,mouseDownPos);
	ofLine(mouseDownPos.x, mouseDownPos.y, p.x, p.y);
	
	
}