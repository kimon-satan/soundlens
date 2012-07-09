/*
 *  mappingEngine.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 08/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "mappingEngine.h"

void mappingEngine::makeMapping(vector<float> inVals, vector<float> & outVals, mapDef m){

	
	//get the range from the data
	if(m.mapType == MAP_1_TO_R){
		
		m.inRange[0] =  999999;
		m.inRange[1] =  -999999;
		
		for(int i = 0; i < inVals.size(); i ++){
			m.inRange[0] = min(inVals[i], m.inRange[0]);
			m.inRange[1] = max(inVals[i], m.inRange[1]);
		}
		
	}
	
	if(m.mapType == MAP_R_TO_EXP){
	
		for(int i = 0; i < inVals.size(); i++){
			
			inVals[i] = ofMap(inVals[i], m.inRange[0], m.inRange[1], 0.0f, 1.0f, true);
			inVals[i] = pow(inVals[i], m.exp);
		}
		
		m.inRange[0] = 0;
		m.inRange[1] = 1;
	}
	
	//make the out range
	
	for(int i = 0; i < inVals.size(); i++){
		
		float f = ofMap(inVals[i], m.inRange[0], m.inRange[1], m.outRange[0], m.outRange[1], true);
		outVals.push_back(f);
	
	}
	

}