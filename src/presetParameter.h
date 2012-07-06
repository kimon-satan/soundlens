/*
 *  presetParameter.h
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

class presetParameter{
	
public:
	
	presetParameter(){
	
		deviation = 0.25;
		range.abs_val = 100;
		range.name = "range";
		increment.abs_val = 0.01;
		increment.name = "increment";
		dType = DT_NONE;
		name = "";
		
	};	
	
	T getValue(int step = 0, int tot = 1){
		
		T r;
		
		static boost::mt19937 randGen;
		static boost::normal_distribution<float> norm(0, deviation);
		boost::variate_generator<boost::mt19937&,boost::normal_distribution<float> > gen(randGen, norm);
		
		switch(dType){
		
			case DT_STEP:
				r = initVal.abs_val + step * increment.abs_val;break;
			case DT_SLICE:
				r = initVal.abs_val + (float)step/tot * increment.abs_val * (float)range.abs_val;
				break;
			case DT_FLAT:
				r = initVal.abs_val + (int)ofRandom(-range.abs_val,range.abs_val) * increment.abs_val;
				break;
			case DT_NORMAL:
				r = max(min(1.0f,gen()),-1.0f) * range.abs_val;
				r = initVal.abs_val + (int)r * increment.abs_val;
				break;
			case DT_CHOOSE:
				r = initVal.abs_val + localVals[(int)(ofRandomf() * localVals.size())];
				break;
			case DT_SEQ:
				r = initVal.abs_val + localVals[step%(int)localVals.size()];
				break;

			default:
				r = initVal.abs_val; break;
			
		}
		
		return r;
	
	
	};
	
	string setUserValues(float ua, float ub){
		
		string pString = "";
		
		pString += initVal.setUserValues(ua,ub);
		pString += increment.setUserValues(ua,ub);
		pString += range.setUserValues(ua,ub);
		if(pString != ""){return name + ": " + pString + "\n";}else{return "";}
	
	};

	
	dataElement<T> initVal;
	dataElement<T> increment; 
	dataElement<int>  range; 
	float deviation; //may need max and min vals for mouse control 
	string name;
	vector<T> localVals;
	e_distributionType dType;
	
};

template <>
class presetParameter <ofVec2f> {
	
public:
	
	presetParameter(){
		
		deviation = 0.25;
		range = 100;
		increment = ofVec2f(1,0);
		dType = DT_NONE;
		
	};	
	
	ofVec2f getValue(int step = 0, int tot = 1){
		
		ofVec2f r;
		float f;
		
		static boost::mt19937 randGen;
		static boost::normal_distribution<float> norm(0, deviation);
		boost::variate_generator<boost::mt19937&,boost::normal_distribution<float> > gen(randGen, norm);
		
		switch(dType){
				
			case DT_STEP:
				r = initVal + step * increment;break;
			case DT_SLICE:
				r = initVal + ((float)step/(float)tot) * increment * range;
			case DT_FLAT:
				r =  initVal + (int)ofRandom(-range,range) * increment;
				r.rotate(ofRandom(0,360),initVal);
				break;
			case DT_NORMAL:
				f = max(min(1.0f,gen()),-1.0f) * range;
				r = initVal + (int)f * increment;
				r.rotate(ofRandom(0,360),initVal);
				break;
			case DT_CHOOSE:
				r = initVal + localVals[(int)(ofRandomf() * localVals.size())];
				break;
			case DT_SEQ:
				r = initVal + localVals[step%(int)localVals.size()];
				break;
			case DT_RADIAL:
				r = (initVal + ofVec2f(0,radius)).rotateRad((float)step * rot,initVal);
				break;
			default:
				r = initVal; break;
				
		}
		
		return r;
		
		
	};
	
	
	ofVec2f initVal, increment; //not sure about increment here ?
	int range; //may need max and min vals for mouse control 
	float deviation; //may need max and min vals for mouse control 
	float radius, rot; //may need max and min vals for mouse control 
	vector<ofVec2f> localVals;
	e_distributionType dType;
	
};


