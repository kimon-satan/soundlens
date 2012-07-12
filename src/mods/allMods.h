/*
 *  allMods.h
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "baseMod.h"
#include "gatherMod.h"
#include "spreadMod.h"

enum e_modType{
	
	MOD_GATHER,
	
	MOD_SPREAD_PREV,
	MOD_SPREAD_PHASE,
	MOD_SPREAD_SPEED,
	MOD_SPREAD_FREQA,
	MOD_SPREAD_FREQB,
	MOD_SPREAD_DECA,
	MOD_SPREAD_DECB,
	
	MOD_COUNT

};

class allMods{

	public:
	
	allMods();
	
	void makeMod(int modType, vector<ofPtr<chime> > targetGrp);
	void drawPreview(int modType,float dragDist, float dragAngle);
	string updateUserValues(int modType, ofVec2f mD, ofVec2f mDr, float ua, float ub);
	
	string getModName(int i);
	
	private:
		
	vector<ofPtr<baseMod> > mods;


};