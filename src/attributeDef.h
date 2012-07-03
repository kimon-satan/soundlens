/*
 *  attributeDef.h
 *  testBed1
 *
 *  Created by Simon Katan on 02/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>

enum e_distributionType{
	
	DT_NONE,
	DT_STEP,
	DT_FLAT,
	DT_NORMAL,
	DT_CHOOSE,
	DT_SEQ,
	DT_RADIAL,
	DT_COUNT,
	
};

template <class T>

class attributeDef{
	
public:
	
	attributeDef(){
	
		deviation = 0.25;
		range = 100;
		increment = 0.01;
		dType = DT_NONE;
		
	};	
	
	T getValue(int step = 0){
		
		T r;
		
		static boost::mt19937 randGen;
		static boost::normal_distribution<float> norm(0, deviation);
		boost::variate_generator<boost::mt19937&,boost::normal_distribution<float> > gen(randGen, norm);
		
		switch(dType){
		
			case DT_STEP:
				r = initVal + step * increment;break;
			case DT_FLAT:
				r = initVal + (int)ofRandom(-range,range) * increment;
				break;
			case DT_NORMAL:
				r = max(min(1.0f,gen()),-1.0f) * range;
				r = initVal + (int)r * increment;
				break;
			case DT_CHOOSE:
				r = initVal + localVals[(int)(ofRandomf() * localVals.size())];
				break;
			case DT_SEQ:
				r = initVal + localVals[step%(int)localVals.size()];
				break;
			default:
				r = initVal; break;
			
		}
		
		return r;
	
	
	};

	
	T initVal;
	T increment; 
	int range;
	float deviation;
	vector<T> localVals;
	e_distributionType dType;
	
};

template <>
class attributeDef <ofVec2f> {
	
public:
	
	attributeDef(){
		
		deviation = 0.25;
		range = 100;
		increment = ofVec2f(1,0);
		dType = DT_NONE;
		
	};	
	
	ofVec2f getValue(int step = 0){
		
		ofVec2f r;
		float f;
		
		static boost::mt19937 randGen;
		static boost::normal_distribution<float> norm(0, deviation);
		boost::variate_generator<boost::mt19937&,boost::normal_distribution<float> > gen(randGen, norm);
		
		switch(dType){
				
			case DT_STEP:
				r = initVal + step * increment;break;
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
	
	
	ofVec2f initVal, increment; 
	int range;
	float deviation;
	float radius, rot;
	vector<ofVec2f> localVals;
	e_distributionType dType;
	
};


