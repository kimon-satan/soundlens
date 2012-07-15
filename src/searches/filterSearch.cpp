/*
 *  filterSearch.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 10/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "filterSearch.h"

filterSearch::filterSearch(int pType){

	dataElement<float> band;
	dataElement<float> q;
	
	int pIndexes[] = {CH_PHASE, CH_SPEED, CH_LENGTH, 4, CH_FREQ, CH_DECAY};
	paramType = pIndexes[pType];
	
	string names[] = {"phase", "speed", "length", "blur", "freq", "decay"};
	float bands[][2] = {{0, b2_pi}, {0, 1.0}, {0.5, 5.0}, {0,1.0}, {MIDI_MIN, MIDI_MIN + MIDI_RANGE}, {0.1,3.0}};
	
	name = "filter_" + names[pType];
	band.name = "band";
	band.set(bands[pType][0], bands[pType][1], SET_USER_B);
	q.name = "bandWidth";
	q.set(0,(bands[pType][1] - bands[pType][0]), SET_USER_A);
	
	
	floatParameters.push_back(band);
	floatParameters.push_back(q);
	
	isSample = false;


}

vector<ofPtr<chime> >filterSearch::getChimes(searchData& sd,ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup){

	vector<ofPtr<chime> > tmp;
	
	for(vector<ofPtr<chime> >::iterator it = searchGroup.begin(); it != searchGroup.end(); it++){
		
		bool isPassed = true;
		
		float lb = floatParameters[0].abs_val - floatParameters[1].abs_val/2;
		lb = max(lb, floatParameters[0].min_val);
		float ub = floatParameters[0].abs_val + floatParameters[1].abs_val/2;
		ub = min(ub, floatParameters[0].max_val);
		

		float val = (paramType != 4)?(*it)->getFixedParam(paramType) : (*it)->getBlur();
		
		if(val < lb || val > ub)isPassed = false;
		
		
		if(isPassed){
			tmp.push_back(*it);
			(*it)->setIsTmpSelected(true);
		}else{
			(*it)->setIsTmpSelected(false);
		}	
		
		
	}
	
	return tmp;

}

void filterSearch::drawPreview(float dragDist, float dragAngle){
	
	float b_ang = -(floatParameters[0].abs_val- floatParameters[0].min_val)/(floatParameters[0].max_val - floatParameters[0].min_val);
	b_ang *= b2_pi * 2;
	float r_ang = -(floatParameters[1].abs_val - floatParameters[1].min_val)/(floatParameters[1].max_val - floatParameters[1].min_val);
	r_ang *= b2_pi;
	
	ofNoFill();
	ofSetColor(150);
	ofCircle(mDown,1.0);
	ofVec2f pnt1(mDown + ofVec2f(0,1.0));
	ofVec2f pnt2(pnt1);
	
	pnt1.rotateRad(min(b_ang - r_ang, 0.0f), mDown);
	pnt2.rotateRad(max(b_ang + r_ang, -b2_pi * 2), mDown);
	ofLine(mDown.x, mDown.y, pnt1.x, pnt1.y); //probably needs to be a filled shape
	ofLine(mDown.x, mDown.y, pnt2.x, pnt2.y);


}