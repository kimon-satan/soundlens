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
#include "presetParameter.h"
#include "allSearches.h"
#include "allMods.h"


struct groupPreset{
	
	groupPreset(){
		
		numChimes.name = "numChimes";
		freq.name = "freq";
		phase.name = "phase";
		speed.name = "speed";
		length.name = "length";
	
	};
	
	string name;
	
	presetParameter<int> numChimes;
	presetParameter<ofVec2f> pos;
	presetParameter<float> freq;
	presetParameter<float> phase;
	presetParameter<float> speed;
	presetParameter<float> length;
	
};

class chimeManager{

	public:
	
	static void setup(ofxOscSender & s , ofxOscSender & i_s);
	static void update();
	static void draw();
	
	static void rePopulateRenderList();
	
	static void shiftFocalPoint(float direction);
	static void shiftZPos(float direction);
	static void nextPrevSelected();
	
	static string createChimes(groupPreset p, ofVec2f pos, float userA, float userB);
	static void endNewChimes();
	
	//search methods
	
	static void newSearch();
	static string continueSearch(int searchType, float userA, float userB);
	static void endSearch();
	static void clearTmps();
	static void selectSample(ofVec2f p);
	
	//mod methods
	
	static string continueMod(int modType, ofVec2f pos, float userA, float userB);
	static void endMod(int modType);
	static void clearAllMods();
	static void clearSelectedMods();
	static void incrementMod(int direction);
	
	
	//rendering 
	
	static void drawSample();
	static void drawSelected();
	static void drawTmpSelected();
	static void drawPreviewChimes();
	static void drawSearchEngine(int searchType, ofVec2f mdown, ofVec2f mdrag, float dragDist, float dragAngle);
	static void drawModEngine(int searchType, ofVec2f mdown, ofVec2f mdrag, float dragDist, float dragAngle);
	
	private:

	static vector<ofPtr<chime> > mChimes;
	
	static vector<ofPtr<chime> > mPreviewChimes;
	static vector<ofPtr<chime> > mSelected;
	static vector<ofPtr<chime> > mTmpSelected;
	
	static vector<vector<ofPtr<chime> > >mPrevSelected;
	static vector<vector<ofPtr<chime> > > renderList;
	
	static int prevSelIndex;
	static float mMaxZ;
	static customListener mListener;
	static ofxOscSender * iSender;
	
	static allSearches mSearchEngine;
	static allMods mModEngine;
	
	
};