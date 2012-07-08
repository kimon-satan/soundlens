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


namespace chimeFactory{

	void initChime(ofPtr<chime> c);
	void createStem(ofPtr<chime> c);
	void createHammer(ofPtr<chime> c);
	void createSensors(ofPtr<chime> c);
	void joinStemBodies(ofPtr<chime> c);


};