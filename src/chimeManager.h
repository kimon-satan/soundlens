/*
 *  chimeManager.h
 *  testBed1
 *
 *  Created by Simon Katan on 02/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "chimeFactory.h"
#include "chimeRenderer.h"
#include "chimeUpdater.h"
#include "attributeDef.h"

struct groupPreset{
	
	string name;
	
	int numChimes;
	attributeDef<ofVec2f> pos;
	attributeDef<float> freq;
	attributeDef<float> iAngle;
	attributeDef<float> speed;
	attributeDef<float> length;
	
};

class chimeManager{

	public:
	
	static void setup(ofxOscSender & s , ofxOscSender & i_s);
	static void update();
	static void draw();
	static void drawSelected();
	
	static void rePopulateRenderList();
	
	static void shiftFocalPoint(float direction);
	static void shiftZPos(float direction);
	static void selectNewGroup();
	
	static void createChimes(groupPreset p, ofVec2f pos);
	
	//selection methods
	
	static void selectByPos(ofVec2f p, float r);
	static void selectByRotSpeed(float rs, float tol);
	
	private:

	static vector<ofPtr<chime> > mChimes;
	static vector<ofPtr<chime> > mSelected;
	static vector<vector<ofPtr<chime> > >mOldGroups;
	static vector<vector<ofPtr<chime> > > renderList;
	
	static int selCGroup;
	static float mMaxZ;
	static customListener mListener;
	static ofxOscSender * iSender;
	
	
};