/*
 *  gatherMod.cpp
 *  testBed1
 * *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "gatherMod.h"

gatherMod::gatherMod(){
	
	dataElement<ofVec2f> pos;
	vecParameters.push_back(pos);
	
	dataElement<float> increment;
	increment.name = "increment";
	increment.set(0.01,0.2, SET_USER_A);
	floatParameters.push_back(increment);

	name = "gatherMod";

}


void gatherMod::makeMod( vector<ofPtr<chime> > chimes){
	
	for(vector<ofPtr<chime> >::iterator it = chimes.begin(); it != chimes.end(); it++){
	
		(*it)->setAnchorTarget(vecParameters[0].abs_val, 0.05f,false);
	
	}
	

}

void gatherMod::drawControl(ofVec2f mouseDownPos, ofVec2f mouseDragPos, float dragDist, float dragAngle){
	
	ofSetColor(100);
	ofNoFill();
	ofCircle(mouseDownPos, dragDist);
	ofLine(mouseDownPos.x, mouseDownPos.y, mouseDragPos.x, mouseDragPos.y);

}