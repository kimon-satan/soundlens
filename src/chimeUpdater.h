/*
 *  chimeUpdater.h
 *  testBed1
 *
 *  Created by Simon Katan on 25/06/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


#include "ofxOsc.h"
#include "chimeFactory.h"

#define TARGET_FRAME 60

class chimeUpdater{
	

	public:
	
	static void update(ofPtr<chime> c);
	static void updateSpIndex(ofPtr<chime> c);
	static void setOscSender(ofxOscSender * s);
	static void step();
	
	static void setFocalPoint(float f);
	static float getFocalPoint();
	
	static void updateDims(ofPtr<chime> c);
	static void reCalcAnchorPoint(ofPtr<chime> c);
	static void conformPhase(ofPtr<chime> c);
	
	
	private:
	
	static void updateSensors(ofPtr<chime> c);
	static void updateModifiables(ofPtr<chime> c);
	
	static unsigned long mTimeStamp1;
	static unsigned long mTimeStamp2;
	static float vel_i, pos_i, timeStep;
	static ofxOscSender * mSender;
	static float mFocalPoint;


};