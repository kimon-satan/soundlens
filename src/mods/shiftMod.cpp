/*
 *  shiftMod.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 16/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "shiftMod.h"

shiftMod::shiftMod(){
	
	dataElement<float> increment;
	increment.name = "increment";
	increment.set(0.01);
	floatParameters.push_back(increment);
	
	name = "shift";

}

vector<ofPtr<chime> > shiftMod::makeMod(vector<ofPtr<chime> > chimes, bool isAuto){

	
	return makeMod(chimes, mDown, floatParameters[0].abs_val, isAuto);

}

vector<ofPtr<chime> > shiftMod::makeMod(vector<ofPtr<chime> > chimes, ofVec2f pos, float inc, bool isAuto){

	vector<ofPtr<chime> >::iterator it;
	
	ofVec2f ave(0,0);
	
	for(it = chimes.begin(); it != chimes.end(); it++)ave += (*it)->getAnchorPos();
	
	ave /= (float)chimes.size();
	
	for(it = chimes.begin(); it != chimes.end(); it++){
		ofVec2f op((*it)->getAnchorPos());
		op -= ave;
		op += pos;
		(*it)->setAnchorTarget(op, inc, isAuto);
	}
	
	return chimes;

}

void shiftMod::drawControl( float dragDist, float dragAngle){

	ofSetColor(100);
	ofNoFill();
	ofCircle(mDown, 0.5 + dragDist);
	ofLine(mDown.x, mDown.y, mDrag.x, mDrag.y);
	
}