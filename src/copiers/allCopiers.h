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
#include "baseMod.h"
#include "copyMod.h"
#include "transpose.h"

enum e_copyType{
	
	TRN_P,
	TRN_S,
	TRN_F,
	TRN_PF,

	COPY_COUNT,
	
};

class allCopiers{
	
public:
	
	allCopiers();
	
	vector <ofPtr<chime> > getCopies(int copyType, vector<ofPtr<chime> > targetGrp);
	void drawPreview(int copyType,float dragDist, float dragAngle);
	
	string updateUserValues(int copyType, ofVec2f mD, ofVec2f mDr, float ua, float ub);
	
	string getCopyName(int i);
	
	void nextGeneration();
	void resetGenCount();
	
private:
	
	vector<ofPtr<baseMod> > copiers;
	
	
};