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
	attributeDef<float> phase;
	attributeDef<float> speed;
	attributeDef<float> length;
	
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
	
	static void createChimes(groupPreset p, ofVec2f pos);
	
	//selection methods
	
	static void newSearch();
	static void endSearch();
	static void clearTmps();
	
	static void selectSample(ofVec2f p);
	
	static void filterBySampleSpeed();
	static void filterByPhaseFundamental(int pf, int tol);
	static void filterByQInterval(int pMul, int pOff);
	
	static void drawSample();
	static void drawSelected();
	static void drawTmpSelected();
	
	private:

	static vector<ofPtr<chime> > mChimes;
	
	static vector<ofPtr<chime> > mSelected;
	static vector<ofPtr<chime> > mTmpSelected;
	
	static vector<vector<ofPtr<chime> > >mPrevSelected;
	static vector<vector<ofPtr<chime> > > renderList;
	
	static int prevSelIndex;
	static float mMaxZ;
	static customListener mListener;
	static ofxOscSender * iSender;
	
	static ofPtr<chime> mSampleChime;
	static float mPhaseTol;
	static int mPhaseFund;
	
};