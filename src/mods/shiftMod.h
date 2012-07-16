/*
 *  shiftMod.h
 *  testBed1
 *
 *  Created by Simon Katan on 16/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "baseMod.h"

class shiftMod : public baseMod {

	
	public:
	
	shiftMod();
	
	vector<ofPtr<chime> >makeMod(vector<ofPtr<chime> > chimes);
	static vector<ofPtr<chime> >makeMod(vector<ofPtr<chime> > chimes, ofVec2f pos, float inc);
	void drawControl( float dragDist, float dragAngle);
	
	private:
	

};