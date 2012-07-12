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
#include "distributionEngine.h"
#include "allSearches.h"
#include "allMods.h"



struct groupPreset{
	
	groupPreset(){
		
		numChimes.setName("numChimes");
		numChimes.setNumVals(1);
		numChimes.setVal(DD_UNIT, 1);
		
		aPos.setName("aPos");
		
		for(int i  =0; i < CH_FLOAT_COUNT; i++){
			distributionDef<float> d;
			d.setName(chime::getChParamString(i));
			fParams.push_back(d);
			
		}
		
	
	};
	
	string name;
	
	vector<distributionDef<float> >fParams;
	vector<mapDef> mapParams;
	
	distributionDef<float> numChimes;
	distributionDef<ofVec2f> aPos;
	
};

class chimeManager{

	public:
	
	static void setup(ofxOscSender & s , ofxOscSender & i_s);
	static void update();
	static void draw();
	
	static void rePopulateRenderList();
	
	static void shiftFocalPoint(float direction);
	static void shiftZPos(float direction);
	
	
	static string createChimes(groupPreset p, ofVec2f pos, float userA, float userB);
	static void endNewChimes();
	
	//search methods
	
	static string getSearchName(int i);
	
	static void newSearch(bool useResults);
	
	static void beginSearch();
	static string continueSearch(int searchType, ofVec2f mD, ofVec2f mDr, float userA, float userB);
	static void endSearch();
	static void clearTmps();
	
	//
	static void switchSelBank(int i);
	static void saveSelBank();
	static void clearSelBanks();
	static void deleteSelBank();
	
	//mod methods
	
	static string getModName(int i);
	
	static string continueMod(int modType, ofVec2f mD, ofVec2f mDr, float userA, float userB);
	static void endMod(int modType);
	static void clearAllMods();
	static void clearSelectedMods();
	static void incrementMod(int direction);
	
	
	//rendering 
	
	static void drawSample();
	static void flashSelected();
	static void drawSelected();
	static void drawTmpSelected();
	static void drawPreviewChimes();
	static void drawSearchEngine(int searchType,float dragDist, float dragAngle);
	static void drawModEngine(int searchType, float dragDist, float dragAngle);
	
	private:

	static vector<ofPtr<chime> > mChimes;
	
	static vector<ofPtr<chime> > mPreviewChimes;
	static vector<ofPtr<chime> > mSelected;
	static vector<ofPtr<chime> > mTmpSelected;
	static vector<vector<ofPtr<chime> > > renderList;
	
	static vector<vector<ofPtr<chime> > >mSelectionBank;
	
	static int sbIndex;
	static float mMaxZ;
	
	static float flashAlpha;
	static bool isNewSelection;
	
	static customListener mListener;
	static ofxOscSender * iSender;
	
	static allSearches mSearchEngine;
	static allMods mModEngine;
	
	
};