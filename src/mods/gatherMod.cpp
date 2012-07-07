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
	increment.set(0.01,0.2, SET_USER_A);
	floatParameters.push_back(increment);

	name = "gather";

}


void gatherMod::makeMod( vector<ofPtr<chime> > chimes){
	
	for(vector<ofPtr<chime> >::iterator it = chimes.begin(); it != chimes.end(); it++){
	
		(*it)->setAnchorTarget(mDown, 0.05f,false);
	
	}
	

}

void gatherMod::drawControl(float dragDist, float dragAngle){
	
	ofSetColor(100);
	ofNoFill();
	ofCircle(mDown, 0.5 + dragDist);
	ofLine(mDown.x, mDown.y, mDrag.x, mDrag.y);

}