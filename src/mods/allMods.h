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

	MSORT_GATHER,
	MSORT_SHIFT,

	MSORT_SPREAD_PREV,
	MSORT_SPREAD_PHASE,

	MSORT_SPREAD_FREQ,
	MSORT_SPREAD_DEC,
	MSORT_SPREAD_SPEED,

	MSORT_SPREAD_SHUFFLE,
	MSORT_SET_MULTI,

	MSORT_COUNT

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
