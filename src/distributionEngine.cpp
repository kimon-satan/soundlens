/*
 *  distributionEngine.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 08/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "distributionEngine.h"

float distributionEngine::getStep(int step, float initVal, float inc){

	return initVal + step * inc;

}


float distributionEngine::getSlice(int step, int numVals, float initVal, float inc, int rng){

	return initVal + (float)step/numVals * inc * (float)rng;
	
}

float distributionEngine::getFlat(float initVal, float inc, int rng){

	return initVal + (int)ofRandom(-rng,rng) * inc;
	
}

float distributionEngine::getNorm(float initVal, float inc, int rng, float dev){

	static boost::mt19937 randGen;
	boost::normal_distribution<float> normDist(0,dev);
	boost::variate_generator<boost::mt19937&,boost::normal_distribution<float> > normGen(randGen, normDist);
	
	float f = max(min(1.0f,normGen()),-1.0f) * rng;
	return initVal + (int)f * inc;
	
}

ofVec2f distributionEngine::getStep(int step, ofVec2f initVal, ofVec2f inc){
	
	return initVal + step * inc;
	
}

ofVec2f distributionEngine::getSlice(int step, int numVals, ofVec2f initVal, ofVec2f inc, int rng){
	
	return initVal + ((float)step/(float)numVals) * inc * rng;
	
}

ofVec2f distributionEngine::getFlat(ofVec2f initVal, ofVec2f inc, int rng){
	
	ofVec2f v =  initVal + (int)ofRandom(-rng,rng) * inc;
	return v.rotate(ofRandom(0,360),initVal);
}

ofVec2f distributionEngine::getNorm(ofVec2f initVal, ofVec2f inc, int rng, float dev){
	
	float f = getNorm(0,0.01,1,dev);
	ofVec2f v = initVal + (int)f * inc * rng;
	return v.rotate(ofRandom(0,360),initVal);
	
}

void distributionEngine::makeValues(vector<int> & vals, distributionDef<int> dDef){
	
	
	for(int i = 0; i < dDef.numVals; i ++){
		
		float f;
		
		switch(dDef.dType){
				
			case DT_STEP:
				f = getStep(i, dDef.initVal.abs_val, dDef.increment.abs_val);break;
			case DT_SLICE:
				f = getSlice(i, dDef.numVals, dDef.initVal.abs_val, dDef.increment.abs_val, dDef.range.abs_val);
				break;
			case DT_FLAT:
				f = getFlat(dDef.initVal.abs_val, dDef.increment.abs_val, dDef.range.abs_val);
				break;
			case DT_NORMAL:
				f = getNorm(dDef.initVal.abs_val, dDef.increment.abs_val, dDef.range.abs_val, dDef.deviation.abs_val);
				break;
			case DT_CHOOSE:
				f = dDef.initVal.abs_val + dDef.localVals[(int)(ofRandomf() * dDef.localVals.size())];
				break;
			case DT_SEQ:
				f = dDef.initVal.abs_val + dDef.localVals[i%(int)dDef.localVals.size()];
				break;
			default:
				f = dDef.initVal.abs_val; break;
				
		}
		
		vals.push_back(f);
	}
	
	
}

void distributionEngine::makeValues(vector<float> & vals, distributionDef<float> dDef){

	
	for(int i = 0; i < dDef.numVals; i ++){
	
		float f;
	
		switch(dDef.dType){
				
			case DT_STEP:
				f = getStep(i, dDef.initVal.abs_val, dDef.increment.abs_val);break;
			case DT_SLICE:
				f = getSlice(i, dDef.numVals, dDef.initVal.abs_val, dDef.increment.abs_val, dDef.range.abs_val);
				break;
			case DT_FLAT:
				f = getFlat(dDef.initVal.abs_val, dDef.increment.abs_val, dDef.range.abs_val);
				break;
			case DT_NORMAL:
				f = getNorm(dDef.initVal.abs_val, dDef.increment.abs_val, dDef.range.abs_val, dDef.deviation.abs_val);
				break;
			case DT_CHOOSE:
				f = dDef.initVal.abs_val + dDef.localVals[(int)(ofRandomf() * dDef.localVals.size())];
				break;
			case DT_SEQ:
				f = dDef.initVal.abs_val + dDef.localVals[i%(int)dDef.localVals.size()];
				break;
			default:
				f = dDef.initVal.abs_val; break;
				
		
		}
	
		vals.push_back(f);
	}
	
	

	
}


void distributionEngine::makeValues(vector<ofVec2f> & vals, distributionDef<ofVec2f> dDef){
	
	
	for(int i = 0; i < dDef.numVals; i ++){
	
		ofVec2f vec;
		
		switch(dDef.dType){
				
			case DT_STEP:
				vec = getStep(i, dDef.initVal.abs_val, dDef.increment.abs_val);
			case DT_SLICE:
				vec = getSlice(i, dDef.numVals, dDef.initVal.abs_val, dDef.increment.abs_val, dDef.range.abs_val);
			case DT_FLAT:
				vec = getFlat(dDef.initVal.abs_val, dDef.increment.abs_val, dDef.range.abs_val);
				break;
			case DT_NORMAL:
				vec = getNorm(dDef.initVal.abs_val, dDef.increment.abs_val, dDef.range.abs_val, dDef.deviation.abs_val);
				break;
			case DT_RADIAL:
				vec = (dDef.initVal.abs_val + ofVec2f(0,dDef.radius.abs_val)).rotateRad((float)i * dDef.rot.abs_val, dDef.initVal.abs_val);
				break;
			case DT_CHOOSE:
				vec = dDef.initVal.abs_val + dDef.localVals[(int)(ofRandomf() * dDef.localVals.size())];
				break;
			case DT_SEQ:
				vec = dDef.initVal.abs_val + dDef.localVals[i%(int)dDef.localVals.size()];
				break;
			default:
				vec = dDef.initVal.abs_val; break;
				
				
		}
		
		vals.push_back(vec);
		
	}


}