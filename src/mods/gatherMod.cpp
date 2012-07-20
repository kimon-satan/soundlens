/*
 *  gatherMod.cpp
 *  testBed1
 * *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "gatherMod.h"

gatherMod::gatherMod(){
	
	
	dataElement<float> increment;
	increment.name = "increment";
	increment.set(0.01,0.2, SET_USER_B);
	floatParameters.push_back(increment);
	
	dataElement<float> rad;
	rad.name = "radius";
	rad.set(0.0,3.0, SET_USER_A);
	floatParameters.push_back(rad);

	name = "gather";

}


vector<ofPtr<chime> > gatherMod::makeMod( vector<ofPtr<chime> > chimes, bool isAuto){
	
	vector<ofPtr<chime> >::iterator it;
	
	float longDist = 0;
	vector<float> distances;
	vector<ofVec2f> nPoints;
	
	for(it = chimes.begin(); it != chimes.end(); it++){
	
		ofVec2f vec =  mDown - (*it)->getAnchorPos();
		vec -= vec.getNormalized() * floatParameters[1].abs_val;
		nPoints.push_back((*it)->getAnchorPos() + vec);
		float d = (*it)->getAnchorPos().distance(mDown);
		if(d > longDist)longDist = d;
		distances.push_back(d);
	
	}
	
	int count = 0;
	
	for(it = chimes.begin(); it != chimes.end(); it++){
		float inc = floatParameters[0].abs_val * distances[count]/longDist;
		(*it)->setAnchorTarget(nPoints[count], inc, isAuto);
		count ++;
	}

	return chimes;
	
}

void gatherMod::drawControl(float dragDist, float dragAngle){
	
	ofSetColor(100);
	ofNoFill();
	ofCircle(mDown, floatParameters[1].abs_val);
	ofLine(mDown.x, mDown.y, mDrag.x, mDrag.y);

}