/*
 *  spreadMod.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 07/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "spreadMod.h"

spreadMod::spreadMod(){
	
	name = "spread";
	
	dataElement<float> rng;
	rng.name = "rng";
	rng.set(1.0,20.0, SET_USER_A);
	floatParameters.push_back(rng);
	
	dataElement<float> ang;
	ang.name = "ang";
	ang.set(180,0,SET_USER_B);
	floatParameters.push_back(ang);
	
}

void spreadMod::makeMod(vector<ofPtr<chime> > chimes){
	
	vector<ofPtr<chime> >::iterator it;
	
	vector<ofVec2f> nPos;
	
	ofVec2f vec(0, floatParameters[0].abs_val);
	vec.rotate(floatParameters[1].abs_val);
	
	
	distributionDef <ofVec2f>dDef;
	dDef.numVals = (int)chimes.size();
	dDef.dType = DT_SLICE;
	dDef.range.abs_val = 1;
	dDef.increment.abs_val = vec;
	dDef.initVal.abs_val = mDown - vec/2;
	
	distributionEngine::makeValues(nPos, dDef);
	
	//now get the longest distance of travel
	
	float longDist = 0;
	vector<float> distances;
	
	int count = 0;
	
	for(it = chimes.begin(); it != chimes.end(); it++){
		
		float d = (*it)->getAnchorPos().distance(nPos[count]);
		if(d > longDist)longDist = d;
		distances.push_back(d);
		count++;
		
	}
	
	count = 0;
	
	for(it = chimes.begin(); it != chimes.end(); it++){
		float inc = 0.02 * distances[count]/longDist;
		(*it)->setAnchorTarget(nPos[count], inc, false);
		count ++;
	}
	
}

void spreadMod::drawControl(float dragDist, float dragAngle){

	ofSetColor(150);
	ofPushMatrix();
	ofNoFill();
	ofCircle(mDown, 0.2);
	ofTranslate(mDown.x, mDown.y, 0);
	ofRotate(floatParameters[1].abs_val,0,0,1);
	ofLine(0,-floatParameters[0].abs_val/2 , 0, floatParameters[0].abs_val/2);
	ofPopMatrix();
	
}