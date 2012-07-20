/*
 *  arrangeCopy.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 14/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "arrangeCopy.h"

arrangeCopy::arrangeCopy(copierSpec cSpec){
	
	name = "arrng(";
	name += chime::getChFixedString(cSpec.chParam) + ")";
	
	paramType = cSpec.chParam;
	
	cSpec.para1.name = "type";
	if(cSpec.para1.setType == SET_FIXED)cSpec.para1.isActive = false;
	cSpec.para1.incr = 1.0;
	cSpec.para1.min_val = 0;
	cSpec.para1.max_val = 4;
	cSpec.para1.displayNames.push_back("rotate");
	cSpec.para1.displayNames.push_back("shuffle");
	cSpec.para1.displayNames.push_back("reverse");
	cSpec.para1.displayNames.push_back("sort - asc");
	
	cSpec.para2.name = "num";
	if(cSpec.para2.setType == SET_FIXED)cSpec.para2.isActive = false;
	cSpec.para2.incr = 1.0;
	
	floatParameters.push_back(cSpec.para1);
	floatParameters.push_back(cSpec.para2);
	
	
}


vector<ofPtr<chime> >arrangeCopy::getCopies(vector<ofPtr<chime> > chimes){
	
	vector<ofPtr<chime> >::iterator it;
	vector<ofPtr<chime> > nChimes;
	
	vector<float> rVals;
	
	for(it = chimes.begin(); it != chimes.end(); it++)rVals.push_back((*it)->getFixedParam(paramType));
	
	if(floatParameters[0].abs_val == 0){
	
		int rot = fmod(floatParameters[1].abs_val, (float)chimes.size()); 
		
		rotate(rVals.begin(), rVals.begin() + rot, rVals.end());
		
	}else if(floatParameters[0].abs_val == 1){
		
		random_shuffle(rVals.begin(), rVals.end()); //could look into making this more subtle at some point
		
	}else if(floatParameters[0].abs_val == 2){
		
		reverse(rVals.begin(), rVals.end());
		
	}else if(floatParameters[0].abs_val == 3){
	
		sort(rVals.begin(), rVals.end());
	
	}
	 
	
	int count = 0;
	
	for(it = chimes.begin(); it != chimes.end(); it++){
		
		ofPtr<chime> c = ofPtr<chime>(new chime());
		
		for(int i = 0; i < CH_FIXED_COUNT - 1; i++){
			
			if(i != paramType){
				
				c->setFixedParam(i, (*it)->getFixedParam(i));
				
			}else{
				
				c->setFixedParam(i,rVals[count]);
				
			}
		}
		
		for(int i = 0; i < CH_MOD_COUNT; i++)c->setModParam(i, (*it)->getModParam(i));
		c->setAnchorPos((*it)->getAnchorPos());
		
		nChimes.push_back(c);
		count ++;
	}
	
	//returns unInitialisedCopies
	
	return nChimes;
	
}

string arrangeCopy::setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub){
	
	baseCopy::setUserData(mD,mDr,ua,ub);
	floatParameters[1].isActive = (floatParameters[0].abs_val == 0);
	return baseCopy::setUserData(mD,mDr,ua,ub);
	
}

