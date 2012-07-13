/*
 *  setMod.h
 *  testBed1
 *
 *  Created by Simon Katan on 13/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "baseMod.h"

class setMod : public baseMod{


	public:
	
	setMod();
	void makeMod(vector<ofPtr<chime> > chimes);
	void drawControl(float dragDist, float dragAngle);
	string setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub);
	
	private:
	
	int paramType;

	


};