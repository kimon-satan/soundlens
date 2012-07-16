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
	vector<ofPtr<chime> > makeMod(vector<ofPtr<chime> > chimes, bool isAuto);
	vector<ofPtr<chime> > makeMod(vector<ofPtr<chime> > chimes){};
	void drawControl(float dragDist, float dragAngle);
	
	private:
	
	

};