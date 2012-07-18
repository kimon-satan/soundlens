



/*
 *  mutate.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 14/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "mutate.h"

mutate::mutate(copierSpec cSpec){
	
	name = "mut(";
	name += chime::getChFixedString(cSpec.chParam) + ")";
	
	paramType = cSpec.chParam;
	
	cSpec.para1.name = "rng";
	if(cSpec.para1.setType == SET_FIXED)cSpec.para1.isActive = false;
	
	floatParameters.push_back(cSpec.para1);
	
	cSpec.para2.name = "dev";
	if(cSpec.para2.setType == SET_FIXED)cSpec.para2.isActive = false;
	
	floatParameters.push_back(cSpec.para2);
	
	
}


vector<ofPtr<chime> >mutate::getCopies(vector<ofPtr<chime> > chimes){
	
	vector<ofPtr<chime> >::iterator it;
	vector<ofPtr<chime> > nChimes;
	
	distributionDef <float> dDef;
	
	dDef.setDType(DT_NORMAL);
	dDef.setInitVal(0);
	dDef.setVal( DD_RNG, 1);
	dDef.setVal( DD_DEV, floatParameters[1].abs_val);
	dDef.setNumVals(chimes.size());
	
	vector<float> mutVals;
	
	distributionEngine::makeValues(mutVals, dDef);
	
	int count = 0;
	
	for(it = chimes.begin(); it != chimes.end(); it++){
		
		ofPtr<chime> c = ofPtr<chime>(new chime());
		
		for(int i = 0; i < CH_FIXED_COUNT - 1; i++){
			
			if(i != paramType){
				
				c->setFixedParam(i, (*it)->getFixedParam(i));
				
			}else{
				
				float f = mutVals[count] * floatParameters[0].abs_val;
				if(paramType == CH_PHASE)f *= b2_pi;
				float val =  (*it)->getFixedParam(i) + f;
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
