/*
 *  spreadMod.h
 *  testBed1
 *
 *  Created by Simon Katan on 07/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "baseMod.h"

class spreadMod : public baseMod{
	
public:
	
	spreadMod();
	void makeMod(vector<ofPtr<chime> > chimes);
	void drawControl(float dragDist, float dragAngle);
	
private:
	
	
	
};