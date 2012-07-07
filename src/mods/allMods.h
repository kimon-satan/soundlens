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
	void drawPreview(int modType, ofVec2f mouseDownPos, ofVec2f mouseDragPos, float dragDist, float dragAngle);
	string updateUserValues(int modType, ofVec2f pos, float ua, float ub);
	
	
	private:
		
	vector<ofPtr<baseMod> > mods;


};