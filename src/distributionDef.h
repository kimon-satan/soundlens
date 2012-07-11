/*
 *  distributionDef.h
 *  testBed1
 *
 *  Created by Simon Katan on 02/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once
#include "dataElement.h"
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>

enum e_distributionType{
	
	DT_NONE,
	DT_STEP,
	DT_SLICE,
	DT_FLAT,
	DT_NORMAL,
	DT_CHOOSE,
	DT_SEQ,
	DT_RADIAL,
	DT_COUNT,
	
};


template <class T>

class distributionDef{
	
public:
	
	distributionDef(){
	
		deviation.abs_val = 0.25;
		deviation.name = "dev";
		range.abs_val = 100;
		range.name = "rng";
		increment.name = "inc";
		dType = DT_NONE;
		name = "";
		numVals = 1;
		overlap.name = "ovrlp";
		overlap.abs_val = 1;
		
	};	
	
	string setUserValues(float ua, float ub){
		
		string pString = "";
		
		pString += initVal.setUserValues(ua,ub);
		pString += increment.setUserValues(ua,ub);
		pString += range.setUserValues(ua,ub);
		pString += deviation.setUserValues(ua,ub);
		pString += radius.setUserValues(ua,ub);
		pString += rot.setUserValues(ua,ub);
		
		if(pString != ""){return name + ": " + pString + "\n";}else{return "";}
	
	};
	
	int numVals;
	dataElement<T> initVal;
	dataElement<T> increment; 
	dataElement<float>  range; 
	dataElement<float>  overlap; 
	dataElement<float> deviation;
	dataElement<float> radius;
	dataElement<float> rot;
	
	string name;
	vector<T> localVals;
	e_distributionType dType;
	
};


