/*
 *  invert.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 14/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "invert.h"

invert::invert(copierSpec cSpec){
	
	name = "invrt(";
	name += chime::getChFixedString(cSpec.chParam) + ")";
	
	paramType = cSpec.chParam;
	
	
}


vector<ofPtr<chime> >invert::getCopies(vector<ofPtr<chime> > chimes){
	
	
	
	vector<ofPtr<chime> >::iterator it;
	vector<ofPtr<chime> > nChimes;
	
	if(chimes.size() < 2)return nChimes;
	
	vector<float> rVals;
	
	float hV = chimes[0]->getFixedParam(paramType);
	float lV = chimes[0]->getFixedParam(paramType);
	
	for(it = chimes.begin(); it != chimes.end(); it++){
		float f = (*it)->getFixedParam(paramType);
		rVals.push_back(f);
		if(f > hV)hV = f;
		if(f < lV)lV = f;
		
	}

	
	
	int count = 0;
	
	for(it = chimes.begin(); it != chimes.end(); it++){
		
		ofPtr<chime> c = ofPtr<chime>(new chime());
		
		for(int i = 0; i < CH_FIXED_COUNT - 1; i++){
			
			if(i != paramType){
				
				c->setFixedParam(i, (*it)->getFixedParam(i));
				
			}else{
				float f = hV + lV - rVals[count];
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


