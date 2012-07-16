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
#include "setMod.h"
#include "shiftMod.h"


enum e_modType{
	
	MOD_SHIFT,
	MOD_GATHER,
	
	MOD_SPREAD_SHUFFLE,
	MOD_SPREAD_PREV,
	MOD_SPREAD_PHASE,
	MOD_SPREAD_SPEED,
	MOD_SPREAD_FREQ,
	MOD_SPREAD_DEC,
	
	MOD_SET_MULTI,
	
	MOD_COUNT

};

class allMods{

	public:
	
	allMods();
	
	void makeMod(int modType, vector<ofPtr<chime> > targetGrp);
	void drawPreview(int modType,float dragDist, float dragAngle);
	string updateUserValues(int modType, ofVec2f mD, ofVec2f mDr, float ua, float ub);
	
	string getModName(int i);
	
	void setIsAuto(bool b);
	
	private:
		
	vector<ofPtr<baseMod> > mods;
	bool isAuto;


};