/*
 *  uniqueSearch.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 16/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "uniqueSearch.h"

uniqueSearch::uniqueSearch(){
	
	name = "unique";
	
	dataElement <int> t_para;
	t_para.name = "parameter";
	t_para.set(0,3,SET_USER_B);
	
	t_para.displayNames.push_back(chime::getChFixedString(CH_PHASE));
	t_para.displayNames.push_back(chime::getChFixedString(CH_SPEED));
	t_para.displayNames.push_back(chime::getChFixedString(CH_FREQ));
	
	t_para.abs_val = 0;
	
	intParameters.push_back(t_para);
	
	float bands[3][2] = {{10,64}, {0.1, 0.01}, {2.0, 0.25}};
	
	for(int i = 0; i < 3; i++){
		
		dataElement <float> toll;
		toll.name = "minDist";
		toll.set(bands[i][0],bands[i][1],SET_USER_A);
		if(i == 0)toll.incr = 1;
		floatParameters.push_back(toll);
		
	}
	
	isSample = false;
	


}


vector<ofPtr<chime> > uniqueSearch::getChimes(searchData& sd, ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup){

	
	vector<ofPtr<chime> > tmp;
	
	vector<ofPtr<chime> >::iterator it;
	vector<ofPtr<chime> >::iterator it2;
	
	float overlap = floatParameters[intParameters[0].abs_val].abs_val;
	
	if(paramType == CH_PHASE)overlap = b2_pi/overlap;
	
	for(it = searchGroup.begin(); it != searchGroup.end(); it++){
		
		bool isUnique = true;
		
		
		for(it2 = tmp.begin(); it2 != tmp.end(); it2++){
			
			float a_val = (*it)->getFixedParam(paramType);
			float b_val = (*it2)->getFixedParam(paramType);
			
			float d = abs(a_val - b_val);
			
			if(paramType == CH_PHASE){
			
				//code to deal with wrapping 
				if(d > b2_pi - overlap){
					
					(a_val < b_val) ? a_val += b2_pi : b_val += b2_pi;
					 
					d = abs(a_val - b_val);
				}
				
			}
			
			if(d < overlap){
				isUnique = false;
				break;
			}
			
		
		}
		
		if(isUnique){
			tmp.push_back(*it);
			(*it)->setIsTmpSelected(true);
		}else{
			(*it)->setIsTmpSelected(false);
		}	
		
	
	}
	
	return tmp;
	
}


string uniqueSearch::setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub){
	
	baseSearch::setUserData(mD,mDr,ua,ub);
	
	int pIndexes[] = {CH_PHASE, CH_SPEED, CH_FREQ};
	paramType = pIndexes[intParameters[0].abs_val];
	
	for(int i = 0; i < 3; i ++)floatParameters[i].isActive = (i == intParameters[0].abs_val);
	
	return baseSearch::setUserData(mD,mDr,ua,ub);
	
}


void uniqueSearch::drawPreview(float dragDist, float dragAngle){
	
	float d = 0.5 + dragDist * 3.0f;
	
	ofNoFill();
	ofSetColor(150);
	ofCircle(mDown,d);
	ofVec2f p(mDown + ofVec2f(0,d));
	p.rotate(-intParameters[0].abs_val * 360/intParameters[0].max_val,mDown);
	ofLine(mDown.x, mDown.y, p.x, p.y);

}