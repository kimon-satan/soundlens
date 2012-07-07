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

enum e_modType{
	
	MOD_GATHER,
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