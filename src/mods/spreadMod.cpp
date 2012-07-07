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

	dataElement<int> slave;
	slave.name = "increment";
	slave.set(0,6, SET_USER_B);
	intParameters.push_back(slave);
	
	name = "spread";
	
}

void spreadMod::makeMod(vector<ofPtr<chime> > chimes){

	
}

void spreadMod::drawControl(float dragDist, float dragAngle){



}