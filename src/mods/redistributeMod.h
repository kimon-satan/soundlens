/*
 *  redistributeMod.h
 *  testBed1
 *
 *  Created by Simon Katan on 12/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "baseMod.h"


class redistributeMod : public baseMod{

	public:
	
	redistributeMod(int pType, int dType);
	vector<ofPtr<chime> > makeMod(vector<ofPtr<chime> > chimes);
	void drawControl(float dragDist, float dragAngle);
	
	private:
	
	int paramType, distType;

};