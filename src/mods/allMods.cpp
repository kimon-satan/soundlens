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

void allMods::drawPreview(int modType, float dragDist, float dragAngle){

	mods[modType]->drawControl(dragDist, dragAngle);
	
}

string allMods::updateUserValues(int modType, ofVec2f mD, ofVec2f mDr, float ua, float ub){

	string s = "";
	s = mods[modType]->setUserData(mD, mDr, ua, ub);
	return s;

}

string allMods::getModName(int i){return mods[i]->getName();}