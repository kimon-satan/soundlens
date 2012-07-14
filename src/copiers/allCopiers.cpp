
#include "allCopiers.h"

/*
 *  allCopiers.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "allCopiers.h"

allCopiers::allCopiers(){
	
	int singleMutes[] = {CH_PHASE, CH_SPEED, CH_FREQ};
	
	for(int i = 0; i < 3; i ++){
	
		vector<int> params;
		params.push_back(singleMutes[i]);
		ofPtr<copyMod> cpm = ofPtr<copyMod>(new copyMod(true, true, params));
		copiers.push_back((ofPtr<baseMod>)cpm);
		
	}
	
	int doubleMutes[][2] = {{CH_PHASE, CH_FREQ}, {CH_SPEED, CH_FREQ}};
	
	for(int i = 0; i < 2; i ++){
		
		vector<int> params;
		for(int j = 0; j < 2; j ++)params.push_back(doubleMutes[i][j]);
		ofPtr<copyMod> cpm = ofPtr<copyMod>(new copyMod(true, true, params));
		copiers.push_back((ofPtr<baseMod>)cpm);
		
	}
	
	for(int i = 0; i < 2; i ++){
		
		vector<int> params;
		for(int j = 0; j < 2; j ++)params.push_back(doubleMutes[i][j]);
		ofPtr<copyMod> cpm = ofPtr<copyMod>(new copyMod(false, true, params));
		copiers.push_back((ofPtr<baseMod>)cpm);
		
	}
	
	
	for(int i = 0; i < 2; i ++){
		
		vector<int> params;
		for(int j = 0; j < 2; j ++)params.push_back(doubleMutes[i][j]);
		ofPtr<copyMod> cpm = ofPtr<copyMod>(new copyMod(false, false, params));
		copiers.push_back((ofPtr<baseMod>)cpm);
		
	}
	

	
	
}


vector <ofPtr<chime> > allCopiers::getCopies(int copyType, vector<ofPtr<chime> > targetGrp){
	
	return copiers[copyType]->makeMod(targetGrp);
	
}


void allCopiers::drawPreview(int copyType, float dragDist, float dragAngle){
	
	copiers[copyType]->drawControl(dragDist, dragAngle);
	
}

string allCopiers::updateUserValues(int copyType, ofVec2f mD, ofVec2f mDr, float ua, float ub){
	
	string s = "";
	s = copiers[copyType]->setUserData(mD, mDr, ua, ub);
	return s;
	
}

string allCopiers::getCopyName(int i){return copiers[i]->getName();}