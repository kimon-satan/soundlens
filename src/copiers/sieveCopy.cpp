

/*
 *  sieveCopy.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 14/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "sieveCopy.h"

sieveCopy::sieveCopy(copierSpec cSpec){
	
	name = "sieve(";
	name += chime::getChFixedString(cSpec.chParam) + ")";
	
	paramType = cSpec.chParam;
	
	cSpec.para1.name = "offset";
	cSpec.para1.incr = 1.0;
	if(cSpec.para1.setType == SET_FIXED)cSpec.para1.isActive = false;

	
	floatParameters.push_back(cSpec.para1);
	
	
}


vector<ofPtr<chime> >sieveCopy::getCopies(vector<ofPtr<chime> > chimes){
	
	
	vector<ofPtr<chime> >::iterator it;
	vector<ofPtr<chime> > nChimes;
	
	tuningEngine::setOffset(floatParameters[0].abs_val);
	
	int count = 0;
	
	for(it = chimes.begin(); it != chimes.end(); it++){
		
		ofPtr<chime> c = ofPtr<chime>(new chime());
		
		for(int i = 0; i < CH_FIXED_COUNT - 1; i++){
			
			if(i != CH_FREQ){
				
				c->setFixedParam(i, (*it)->getFixedParam(i));
				
			}else{
				
				float f = tuningEngine::getNearestNeighbour((*it)->getFixedParam(i));
				c->setFixedParam(i,f);
				
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


