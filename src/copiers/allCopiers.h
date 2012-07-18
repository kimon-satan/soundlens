/*
 *  allCopiers.h
 *  testBed1
 *
 *  Created by Simon Katan on 14/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "chimeUpdater.h"
#include "shiftMod.h"
#include "baseCopy.h"
#include "transpose.h"
#include "mutate.h"

enum e_copyType{
	
	CP_TRANSPOSE,
	CP_MUTATE,
	CP_ROTATE,
	CP_SHUFFLE,
	CP_INVERT,
	CP_REVERSE,
	CP_EXPAND,
	CP_CONTRACT,
	CP_SIEVE,

	COPY_COUNT
	
};



struct copyPreset{
	
	string name;
	vector<copierSpec> copiers;
	
};



class allCopiers{
	
public:
	
	allCopiers();
	
	void beginCopy(copyPreset cp);
	vector <ofPtr<chime> > getCopies(vector<ofPtr<chime> > targetGrp);
	void drawPreview(float dragDist, float dragAngle);
	
	string updateUserValues(ofVec2f mD, ofVec2f mDr, float ua, float ub);
	
	void nextGeneration();
	void resetGenCount();
	
private:
	
	vector<ofPtr<baseCopy> > copiers;
	
	ofVec2f mDown, mDrag;
	
	
};