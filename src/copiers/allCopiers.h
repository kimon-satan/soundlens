/*
 *  allCopiers.h
 *  testBed1
 *
 *  Created by Simon Katan on 14/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "baseMod.h"
#include "copyMod.h"

enum e_copyType{
	
	COPY_P,
	COPY_S,
	COPY_F,
	COPY_PF_II,
	COPY_SF_II,
	COPY_PF_LI,
	COPY_SF_LI,
	COPY_PF_LL,
	COPY_SF_LL,
	COPY_COUNT,
	
};

class allCopiers{
	
public:
	
	allCopiers();
	
	vector <ofPtr<chime> > getCopies(int copyType, vector<ofPtr<chime> > targetGrp);
	void drawPreview(int copyType,float dragDist, float dragAngle);
	
	string updateUserValues(int copyType, ofVec2f mD, ofVec2f mDr, float ua, float ub);
	
	string getCopyName(int i);
	
private:
	
	vector<ofPtr<baseMod> > copiers;
	
	
};