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
	
	vector<ofPtr<chime> >makeMod(vector<ofPtr<chime> > chimes, bool isAuto);
	static vector<ofPtr<chime> >makeMod(vector<ofPtr<chime> > chimes, ofVec2f pos, float inc, bool isAuto);
	vector<ofPtr<chime> > makeMod(vector<ofPtr<chime> > chimes){};
	void drawControl( float dragDist, float dragAngle);
	
	private:
	

};