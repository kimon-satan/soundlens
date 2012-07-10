/*
 *  multiFilterSearch.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 10/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "multiFilterSearch.h"

multiFilterSearch::multiFilterSearch(bool isHpass){

	mIsHighPass = isHpass;
	
	name = (mIsHighPass) ? "HPfilter" : "LPfilter";
	
	dataElement <int> t_para;
	t_para.name = "parameter";
	t_para.set(0,6,SET_USER_B);
	
	for(int i = 0; i < 3; i ++)t_para.displayNames.push_back(chime::getChParamString(i));
	
	t_para.displayNames.push_back("blur");
	t_para.displayNames.push_back("freq");
	t_para.displayNames.push_back("decay");
	
	t_para.abs_val = 0;
	
	intParameters.push_back(t_para);
	
	
	float bands[][2] = {{0, b2_pi}, {0, 1.0}, {0.5, 5.0}, {0,1.0}, {MIDI_MIN, MIDI_MIN + MIDI_RANGE}, {0.1,3.0}};
	
	for(int i = 0; i < 6; i++){
		
		dataElement <float> t_rng;
		t_rng.name = "cutOff";
		t_rng.set(bands[i][0],bands[i][1],SET_USER_A);
		floatParameters.push_back(t_rng);
		
	}
	
	paramType = 0;
	isSample = false;
	
}


vector<ofPtr<chime> > multiFilterSearch::getChimes(searchData& sd,ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup){

	float fp = floatParameters[paramType].abs_val;
	
	vector<ofPtr<chime> > tmp;
	
	for(vector<ofPtr<chime> >::iterator it = searchGroup.begin(); it != searchGroup.end(); it++){
		
		bool isPassed = true;
		
		int pIndexes[] = {CH_PHASE, CH_SPEED, CH_LENGTH, CH_BLUR, CH_FREQ_A, CH_DECAY_A};
		int p_index = pIndexes[paramType];
		
		int numTests = (paramType != PT_FREQ || paramType != PT_DECAY)? 1 : 2;
		
		for(int i = 0; i < numTests; i ++){
			
			float val = (p_index != CH_BLUR)?(*it)->getModParam(p_index + i) : (*it)->getBlur();
			
			if(mIsHighPass){
				if(val <  fp)isPassed = false;
			}else{
				if(val > fp)isPassed = false;
			}
		}
		
		if(isPassed){
			tmp.push_back(*it);
			(*it)->setIsTmpSelected(true);
		}else{
			(*it)->setIsTmpSelected(false);
		}	
	}
	
	return tmp;
	
}

string multiFilterSearch::setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub){
	
	baseSearch::setUserData(mD,mDr,ua,ub);
	
	paramType = intParameters[0].abs_val;
	
	for(int i = 0; i < 6; i ++)floatParameters[i].isActive = (i == paramType);
	
	return baseSearch::setUserData(mD,mDr,ua,ub);
	
}


void multiFilterSearch::drawPreview(float dragDist, float dragAngle){

	float d = 0.5 + floatParameters[paramType].abs_val * 3.0f/(float)floatParameters[paramType].max_val;
	
	ofNoFill();
	ofSetColor(150);
	ofCircle(mDown,d);
	ofVec2f p(mDown + ofVec2f(0,d));
	p.rotate(-intParameters[0].abs_val * 360/intParameters[0].max_val,mDown);
	ofLine(mDown.x, mDown.y, p.x, p.y);
	

}