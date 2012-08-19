

/*
 *  transpose.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 14/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "transpose.h"

transpose::transpose(copierSpec cSpec){
	
	name = "tr(";
	name += chime::getChFixedString(cSpec.chParam) + ")";
	
	paramType = cSpec.chParam;
	
	cSpec.para1.name = "amt";
	if(cSpec.para1.setType == SET_FIXED)cSpec.para1.isActive = false;
	
	floatParameters.push_back(cSpec.para1);
	
}


vector<ofPtr<chime> >transpose::getCopies(vector<ofPtr<chime> > chimes){
	
	vector<ofPtr<chime> >::iterator it;
	vector<ofPtr<chime> > nChimes;
	
	int count = 0;
	
	for(it = chimes.begin(); it != chimes.end(); it++){
		
		ofPtr<chime> c = ofPtr<chime>(new chime());
		
		for(int i = 0; i < CH_FIXED_COUNT - 1; i++){
			
			if(i != paramType){
				
				c->setFixedParam(i, (*it)->getFixedParam(i));
				
			}else{
				
				float f = (i == CH_PHASE) ?  b2_pi * floatParameters[0].abs_val : floatParameters[0].abs_val;
				float val =  (i == CH_SPEED) ?  (*it)->getFixedParam(i) * f : (*it)->getFixedParam(i) + f;
				c->setFixedParam(i,val);
				
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
