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
	
	ofPtr<setMod> sm = ofPtr<setMod>(new setMod());
	mods.push_back((ofPtr<baseMod>)sm);
	
	ofPtr<gatherMod> gm = ofPtr<gatherMod>(new gatherMod());
	mods.push_back((ofPtr<baseMod>)gm);
	
	for(int i = -2; i < 4; i++){
		ofPtr<spreadMod> spm = ofPtr<spreadMod>(new spreadMod(i));
		mods.push_back((ofPtr<baseMod>)spm);
	}
	
	for(int i = 0; i < 7; i ++){
		for(int j = 0; j < 5; j++){
			ofPtr<redistributeMod> rdm = ofPtr<redistributeMod>(new redistributeMod(j,i));
			mods.push_back((ofPtr<baseMod>)rdm);
		}
	
	}

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