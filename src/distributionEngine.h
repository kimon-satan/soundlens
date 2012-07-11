/*
 *  distributionEngine.h
 *  testBed1
 *
 *  Created by Simon Katan on 08/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once 

#include "distributionDef.h"
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>


class distributionEngine{

	public:
	
	static void makeValues(vector<float> & vals, distributionDef<float> dDef);
	static void makeValues(vector<ofVec2f> & vals, distributionDef<ofVec2f> dDef);
	static void makeValues(vector<int> & vals, distributionDef<int> dDef);
	
	private:
	
	static float getStep(int step, float initVal, float inc, float rng = 0);
	static float getSlice(int step, int numVals, float initVal, float inc, float rng);
	static float getFlat(float initVal, float inc, float rng);
	static float getNorm(float initVal, float inc, float rng, float dev);
	
	static ofVec2f getStep(int step, ofVec2f initVal, ofVec2f inc, float rng);
	static ofVec2f getSlice(int step, int numVals, ofVec2f initVal, ofVec2f inc, float rng);
	static ofVec2f getFlat(ofVec2f initVal, ofVec2f inc, float rng);
	static ofVec2f getNorm(ofVec2f initVal, ofVec2f inc, float rng, float dev);


};