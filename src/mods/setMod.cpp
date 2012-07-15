/*
 *  setMod.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 13/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "setMod.h"

setMod::setMod(){

	dataElement <int> t_para;
	t_para.name = "parameter";
	t_para.set(0, CH_MOD_COUNT, SET_USER_B);
	
	for(int i = 0; i < CH_MOD_COUNT; i ++)t_para.displayNames.push_back(chime::getChModString(i));
	
	t_para.abs_val = 0;
	
	intParameters.push_back(t_para);
	
	
	float bands[][2] = {
						{0,5}, //num
						{-3,3},	
						{0,4.0},
						{-1.0,1.0}};
	
	float incs[] = {1,0.05,0.05,0.05};
	
	for(int i = 0; i < CH_MOD_COUNT; i++){
		
		dataElement <float> t_rng;
		t_rng.name = "val";
		t_rng.set(bands[i][0],bands[i][1],SET_USER_A);
		t_rng.incr = incs[i];
		floatParameters.push_back(t_rng);
		
	}
	
	name = "pivots";
	
	

}


vector<ofPtr<chime> > setMod::makeMod(vector<ofPtr<chime> > chimes){
	
	vector<ofPtr<chime> >::iterator it;
	
	float longDist = 0;
	vector<float> distances;
	
	
	//calculate the distances
	
	for(it = chimes.begin(); it != chimes.end(); it++){
		
		float d = abs((*it)->getModParam(intParameters[0].abs_val) - floatParameters[intParameters[0].abs_val].abs_val);
		if(d > longDist)longDist = d;
		distances.push_back(d);
		
	}
	
	float inc = (intParameters[0].abs_val == CH_PIV_LGTH)? 0.01 : 0.001;
	
	//set the targets
	int count = 0;
	
	
	for(it = chimes.begin(); it != chimes.end(); it++){

		(*it)->flagModParam(intParameters[0].abs_val);
		(*it)->setModParam(intParameters[0].abs_val , floatParameters[intParameters[0].abs_val].abs_val);
	
		count ++;
	}
	
	return chimes;
}

string setMod::setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub){
	
	baseMod::setUserData(mD,mDr,ua,ub);
	
	for(int i = 0; i < CH_MOD_COUNT; i ++)floatParameters[i].isActive = (i == intParameters[0].abs_val);
	
	return baseMod::setUserData(mD,mDr,ua,ub);
	
}


void setMod::drawControl(float dragDist, float dragAngle){

	float d = 0.5 + dragDist * 3;
	
	ofNoFill();
	ofSetColor(150);
	ofCircle(mDown,d);
	ofVec2f p(mDown + ofVec2f(0,d));
	p.rotate(-intParameters[0].abs_val * 360/intParameters[0].max_val,mDown);
	ofLine(mDown.x, mDown.y, p.x, p.y);

}