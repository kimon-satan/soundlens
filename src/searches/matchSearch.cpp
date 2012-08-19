/*
 *  matchSearch.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "matchSearch.h"

matchSearch::matchSearch(){

	name = "match";
	isSample = true;
	isMDrag = false;
	
	dataElement <int> t_para;
	t_para.name = "parameter";
	t_para.set(0,5,SET_USER_B);
	
	for(int i = 0; i < 5; i ++)t_para.displayNames.push_back(chime::getChFixedString(i));
	
	t_para.abs_val = 0;
	
	intParameters.push_back(t_para);
	
	//phase, speed, length, freq, decay, 
	
	float tolMaxs[5] =  {0.5, 0.2, 1, 6, 1};
	
	for(int i = 0; i < 5; i++){
	
		dataElement <float> t_tol;
		t_tol.name = "tollerance";
		t_tol.set(0,tolMaxs[i],SET_USER_A);
		floatParameters.push_back(t_tol);
	
	}
	
	mTolIndex = 0;
	
	
	
}

vector<ofPtr<chime> > matchSearch::getChimes(searchData& sd, ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup){
	
	vector<ofPtr<chime> > tmp;
	
	for(vector<ofPtr<chime> >::iterator it = searchGroup.begin(); it != searchGroup.end(); it++){
	
		//prepare the values
		
		bool isMatches = false;
		
		float sVal;
		float itVal; 
		
		
		sVal = sample->getFixedParam(mTolIndex);
		itVal = (*it)->getFixedParam(mTolIndex);
			

		//the tests
	
		if(itVal >= sVal - mTol && itVal <= sVal + mTol)isMatches = true;
			
				
		//now push it back
		
		if(isMatches){
			tmp.push_back(*it);
			(*it)->setIsTmpSelected(true);
		}else{
			(*it)->setIsTmpSelected(false);
		}	
	
	} //end of it loop
	
	return tmp;

}

string matchSearch::setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub){
	
	baseSearch::setUserData(mD,mDr,ua,ub);
	
	mTolIndex = intParameters[0].abs_val;
	mTol = floatParameters[mTolIndex].abs_val;
	if(mTolIndex == CH_PHASE)mTol *= b2_pi;
	
	for(int i = 0; i < 5; i ++)floatParameters[i].isActive = (i == mTolIndex);
	
	return baseSearch::setUserData(mD,mDr,ua,ub);

}

void matchSearch::drawPreview(float dragDist, float dragAngle){
	
	//may end up as a method in baseSearch for reuse
	
	float d = 0.5 + floatParameters[mTolIndex].abs_val * 3.0f/(float)floatParameters[mTolIndex].max_val;
	
	ofNoFill();
	ofSetColor(150);
	ofCircle(mDown,d);
	ofVec2f p(mDown + ofVec2f(0,d));
	p.rotate(-intParameters[0].abs_val * 360/intParameters[0].max_val,mDown);
	ofLine(mDown.x, mDown.y, p.x, p.y);

}