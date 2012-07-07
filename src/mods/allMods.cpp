/*
 *  allMods.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "allMods.h"

allMods::allMods(){

	ofPtr<gatherMod> gm = ofPtr<gatherMod>(new gatherMod());
	mods.push_back((ofPtr<gatherMod>)gm);

}

void allMods::makeMod(int modType, vector<ofPtr<chime> > targetGrp){

	mods[modType]->makeMod(targetGrp);
	
}

void allMods::drawPreview(int modType, ofVec2f mouseDownPos, ofVec2f mouseDragPos, float dragDist, float dragAngle){

	mods[modType]->drawControl(mouseDownPos, mouseDragPos, dragDist, dragAngle);
	
}

string allMods::updateUserValues(int modType, ofVec2f pos, float ua, float ub){

	string s = "";
	s = mods[modType]->setUserData(pos, ua, ub);
	return s;

}