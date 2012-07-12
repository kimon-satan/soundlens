/*
 *  distributionEngine.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 08/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "distributionEngine.h"

//floats -----------------------------

float distributionEngine::getStep(int step, float initVal, float rng, float unit, float dev){
	
	float f = initVal + step * unit + (unit * ofRandom(-dev,dev));
	if(rng > 0)f = fmod((float)f ,rng); //for when overlaps the rng
	return f;

}


float distributionEngine::getSlice(int step, int numVals, float initVal, float rng, float unit, float dev){
	
	float f = (float)step/(float)numVals * rng;
	if(unit > 0)f -= fmod(f, unit);
	f += f * ofRandom(-dev, dev);
	return initVal + f;	
	
}

float distributionEngine::getFlat(float initVal, float rng, float unit){

	float f = ofRandom(-rng/2.0f,rng/2.0f); 
	if(unit > 0) f -= fmod(f, unit);
	return initVal + f;
	
}

float distributionEngine::getNorm(float initVal, float rng, float unit, float dev){

	static boost::mt19937 randGen;
	boost::normal_distribution<float> normDist(0,dev);
	boost::variate_generator<boost::mt19937&,boost::normal_distribution<float> > normGen(randGen, normDist);
	
	float f = max(min(1.0f,normGen()),-1.0f) * rng/2.0f;
	if(unit > 0)f -= fmod(f,unit);
	return initVal + f;
	
}


void distributionEngine::makeValues(vector<float> & vals, distributionDef<float> dDef){
	
	
	for(int i = 0; i < dDef.getNumVals(); i ++){
		
		float f;
		
		switch(dDef.getDType()){
				
			case DT_STEP:
				f = getStep(i, dDef.getInitVal(), dDef.getVal(DD_RNG), dDef.getVal(DD_UNIT), dDef.getVal(DD_DEV));
				break;
			case DT_SLICE:
				f = getSlice(i,  dDef.getNumVals(), dDef.getInitVal(), dDef.getVal(DD_RNG), dDef.getVal(DD_UNIT), dDef.getVal(DD_DEV));
				break;
			case DT_FLAT:
				f = getFlat(dDef.getInitVal(), dDef.getVal(DD_RNG), dDef.getVal(DD_UNIT));
				break;
			case DT_NORMAL:
				f = getNorm(dDef.getInitVal(), dDef.getVal(DD_RNG), dDef.getVal(DD_UNIT), dDef.getVal(DD_DEV));
				break;
			case DT_CHOOSE:
				f = dDef.getInitVal() + dDef.getLocalVals().at(ofRandom(0,dDef.getLocalVals().size()-1));
				break;
			case DT_SEQ:
				f = dDef.getInitVal() + dDef.getLocalVals().at(i%(int)dDef.getLocalVals().size());
				break;
			default:
				f = dDef.getInitVal(); 
				break;
				
		}
		
		vals.push_back(f);
	}
	
	
	
	
}



//vecs ------------------------------------------------------------------------------------

ofVec2f distributionEngine::getStep(int step, ofVec2f initVal, ofVec2f rngVec, float unit, float dev){
	
	//the equivalent of the float method
	
	ofVec2f v(rngVec);
	v.normalize();
	v *= unit * (float)step;
	if(v.length() > rngVec.length())v -= rngVec;
	
	return initVal + v;
	
}

ofVec2f distributionEngine::getSlice(int step, int numVals, ofVec2f initVal, ofVec2f rngVec, float unit, float dev){
	
	ofVec2f v(rngVec);
	v.normalize();
	
	float f = (float)step/(float)numVals * rngVec.length();
	if(unit > 0)f -= fmod(f, unit);
	f += f * ofRandom(-dev, dev);
	
	v *= f;
	
	return initVal + v;	
	
}

ofVec2f distributionEngine::getFlat(ofVec2f initVal, ofVec2f rngVec, float unit){
		
	ofVec2f v(rngVec);
	v.normalize();
	
	float f = ofRandom(0,rngVec.length()); 
	if(unit > 0) f -= fmod(f, unit);
	
	v *= f;
	
	return initVal -(rngVec/2) + v;

}

ofVec2f distributionEngine::getNorm(ofVec2f initVal, ofVec2f rngVec, float unit, float dev){
	
	ofVec2f v(rngVec);
	v.normalize();
	
	float f = getNorm(0,rngVec.length(),unit, dev);
	
	v *= f; 
	
	return initVal -(rngVec/2) + v;
	
}





void distributionEngine::makeValues(vector<ofVec2f> & vals, distributionDef<ofVec2f> dDef){
	
	
	for(int i = 0; i < dDef.getNumVals(); i ++){
	
		ofVec2f vec;
		
		switch(dDef.getDType()){
				
			case DT_STEP:
				vec = getStep(i, dDef.getInitVal(), dDef.getRngVec(), dDef.getVal(DD_UNIT), dDef.getVal(DD_DEV));
				break;
			case DT_SLICE:
				vec = getSlice(i, dDef.getNumVals(),dDef.getInitVal(), dDef.getRngVec(), dDef.getVal(DD_UNIT), dDef.getVal(DD_DEV));
				break;
			case DT_FLAT:
				vec = getFlat(dDef.getInitVal(), dDef.getRngVec(), dDef.getVal(DD_UNIT));
				break;
			case DT_NORMAL:
				vec = getNorm(dDef.getInitVal(), dDef.getRngVec(), dDef.getVal(DD_UNIT), dDef.getVal(DD_DEV));
				break;
			case DT_CHOOSE:
				vec = dDef.getInitVal() + dDef.getLocalVals().at((int)(ofRandomf() * dDef.getLocalVals().size()));
				break;
			case DT_SEQ:
				vec = dDef.getInitVal() + dDef.getLocalVals().at(i%(int)dDef.getLocalVals().size());
				break;
			default:
				vec = dDef.getInitVal(); 
				break;				
				
		}
		
		vals.push_back(vec);
		
	}


}