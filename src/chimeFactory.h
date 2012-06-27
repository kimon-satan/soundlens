/*
 *  chimeFactory.h
 *  testBed1
 *
 *  Created by Simon Katan on 25/06/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "myUtils.h"
#include "chime.h"




struct chimeDef{
	
	vector<pivotDims> pivots; 
	ofVec2f anchorPos;
	float length, freq, iAngle, offset, rSpeed;
	
};

namespace chimeFactory{

	ofPtr<chime> createChime(chimeDef cd);
	
	void createStem(ofPtr<chime> c);
	void createHammer(ofPtr<chime> c);
	void createSensors(ofPtr<chime> c);
	void joinStemBodies(ofPtr<chime> c);


};