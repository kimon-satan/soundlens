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
#include "mappingEngine.h"

namespace chimeFactory{

	void initBodies(ofPtr<chime> c);
	
	void conformPhase(ofPtr<chime> c);
	void mapFreqToSensors(ofPtr<chime> c); //this probably should be elsewhere
	
	void changeSpeed(ofPtr <chime> c);
	void changeLength(ofPtr <chime> c);
	void changePhase(ofPtr <chime> c);
	
	void createStem(ofPtr<chime> c);
	void createHammer(ofPtr<chime> c);
	void createSensors(ofPtr<chime> c);
	void joinStemBodies(ofPtr<chime> c);
	void makePivots(ofPtr<chime> c);


};