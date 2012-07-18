/*
 *  tuningEngine.h
 *  testBed1
 *
 *  Created by Simon Katan on 17/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#define NUM_SCALES 103

class tuningEngine{


	public:	
	
	static string getCScaleName();
	static void changeCScale(int i);
	static void requestScale();
	static void setSender(ofxOscSender * s);
	static void setReciever(ofxOscReceiver * r);
	static void handleMessages();
	static void setOffset(float f);
	static bool checkForMatch(float f, float toll);
	static float getNearestNeighbour(float f);
	
	private:
	
	static const string scaleNames[];
	static int cScale;
	static ofxOscSender * mSender;
	static ofxOscReceiver * mReceiver;
	static vector<float> mMidiNotes;
	static vector<float> mOffsetMidiNotes;
	static float mOffset;
	

};