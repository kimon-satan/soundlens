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
	t_para.set(0,7,SET_USER_B);
	
	for(int i = 0; i < 3; i ++)t_para.displayNames.push_back(chime::getChParamString(i));
	
	t_para.displayNames.push_back("freq(OR)");
	t_para.displayNames.push_back("decay(OR)");
	t_para.displayNames.push_back("freq(AND)");
	t_para.displayNames.push_back("decay(AND)");
	
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
		
		float sVal[2];
		float itVal[2]; 
		
		if(mTolIndex < 3){
		
			sVal[0] = sample->getModParam(mTolIndex);
			itVal[0] = (*it)->getModParam(mTolIndex);
			
		}else{
		
			int para = (mTolIndex == 3) ? CH_FREQ_A: CH_DECAY_A;
				
			for(int i = 0; i < 2; i++){
				sVal[i] = sample->getModParam(para + i);
				itVal[i] = (*it)->getModParam(para + i);
			}
			
		}
		
		//the tests
		
		if(matchType == MATCH_SIMPLE){
	
			if(itVal[0] >= sVal[0] - mTol && itVal[0] <= sVal[0] + mTol)isMatches = true;
			
		}else if(matchType == MATCH_OR){
		
				
			for(int i = 0;i < 2; i++){
				if((itVal[i] >= sVal[0] -mTol && itVal[i] <= sVal[0] + mTol)||
				    (itVal[i] >= sVal[1] - mTol && itVal[i] <= sVal[1] + mTol)
				){
					isMatches = true;break;
				}
			}
	
		}else{
			
			for(int i = 0;i < 2; i++){
				if((itVal[0] >=  sVal[i] - mTol && itVal[0] <=  sVal[i] + mTol) && 
				   (itVal[1] >=  sVal[(i+1)%2] - mTol && itVal[1] <=  sVal[(i+1)%2] + mTol)
				   ){
					isMatches = true;
					break;
				}
			}
			
		}
		
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
	if(mTolIndex == 0)mTol *= b2_pi;
	
	if(mTolIndex < 3)
		matchType = MATCH_SIMPLE;
	else if(mTolIndex < 5)
		matchType = MATCH_OR;
	else
		matchType = MATCH_AND;
	
	if(mTolIndex  == 3 || mTolIndex  == 5)mTolIndex = 3; 
	if(mTolIndex  == 4 || mTolIndex  == 6)mTolIndex = 4; 
	
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