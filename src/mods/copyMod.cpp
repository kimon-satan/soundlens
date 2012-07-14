/*
 *  copyMod.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 14/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "copyMod.h"

copyMod::copyMod(){


	
}


vector<ofPtr<chime> >copyMod::makeMod(vector<ofPtr<chime> > chimes){

	vector<ofPtr<chime> > nChimes;
	
	for(vector<ofPtr<chime> >::iterator it = chimes.begin(); it != chimes.end(); it++){
	
		ofPtr<chime> c = ofPtr<chime>(new chime());
		
		// straight copy
		
		for(int i = 0; i < CH_FLOAT_COUNT; i++)c->setModParam(i, (*it)->getModParam(i));
		c->setAnchorPos((*it)->getAnchorPos());
		c->setSensorColor((*it)->getSensorColor());
		c->setZpos((*it)->getZpos()); //potentially not
	
		nChimes.push_back(c);
	
	}
	
	//returns empty copies
	return nChimes;
	
}

void copyMod::drawControl( float dragDist, float dragAngle){
	
	ofNoFill();
	ofSetColor(150);
	ofCircle(mDown,0.5);
	ofLine(mDown.x, mDown.y, mDrag.x, mDrag.y);


}