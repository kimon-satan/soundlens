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

#define NUM_CHIMES 30

class chimeManager{

	public:
	
	static void setup(ofxOscSender & s , ofxOscSender & i_s);
	static void update();
	static void draw();
	
	static void setupChimes();
	static void rePopulateRenderList();
	
	static void shiftFocalPoint(float direction);
	static void shiftZPos(float direction);
	static void selectNewGroup();
	
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