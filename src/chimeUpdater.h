/*
 *  chimeUpdater.h
 *  testBed1
 *
 *  Created by Simon Katan on 25/06/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "chime.h"
#include "ofxOsc.h"


class chimeUpdater{
	

	public:
	
	static void update(ofPtr<chime> c);
	static void setOscSender(ofxOscSender * s);
	
	private:
	
	static float vel_i, pos_i, timeStep;
	static ofxOscSender * mSender;

};