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
#include "redistributeMod.h"

enum e_modType{
	
	MOD_GATHER,
	
	MOD_SPREAD_SHUFFLE,
	MOD_SPREAD_PREV,
	MOD_SPREAD_PHASE,
	MOD_SPREAD_SPEED,
	MOD_SPREAD_FREQ,
	MOD_SPREAD_DEC,
	
	//redist mods
	
	MOD_RD_SINGLE_PHASE,
	MOD_RD_SINGLE_SPEED,
	MOD_RD_SINGLE_LENGTH,
	MOD_RD_SINGLE_FREQ,
	MOD_RD_SINGLE_DEC,
	
	MOD_RD_STEP_PHASE,
	MOD_RD_STEP_SPEED,
	MOD_RD_STEP_LENGTH,
	MOD_RD_STEP_FREQ,
	MOD_RD_STEP_DEC,
	
	MOD_RD_SLICE_PHASE,
	MOD_RD_SLICE_SPEED,
	MOD_RD_SLICE_LENGTH,
	MOD_RD_SLICE_FREQ,
	MOD_RD_SLICE_DEC,
	
	MOD_RD_FLAT_PHASE,
	MOD_RD_FLAT_SPEED,
	MOD_RD_FLAT_LENGTH,
	MOD_RD_FLAT_FREQ,
	MOD_RD_FLAT_DEC,
	
	MOD_RD_NORMAL_PHASE,
	MOD_RD_NORMAL_SPEED,
	MOD_RD_NORMAL_LENGTH,
	MOD_RD_NORMAL_FREQ,
	MOD_RD_NORMAL_DEC,
	
	MOD_RD_CHOOSE_PHASE,
	MOD_RD_CHOOSE_SPEED,
	MOD_RD_CHOOSE_LENGTH,
	MOD_RD_CHOOSE_FREQ,
	MOD_RD_CHOOSE_DEC,
	
	MOD_RD_SEQ_PHASE,
	MOD_RD_SEQ_SPEED,
	MOD_RD_SEQ_LENGTH,
	MOD_RD_SEQ_FREQ,
	MOD_RD_SEQ_DEC,
	
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