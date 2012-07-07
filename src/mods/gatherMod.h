/*
 *  gatherMod.h
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "baseMod.h"

class gatherMod : public baseMod{

	public:
	
	gatherMod();
	void makeMod(vector<ofPtr<chime> > chimes);
	void drawControl(ofVec2f mouseDownPos, ofVec2f mouseDragPos, float dragDist, float dragAngle);
	
	private:
	
	

};