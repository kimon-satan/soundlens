/*
 *  baseSearch.h
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "dataElement.h"
#include "chime.h"

struct searchData{
	
	float phaseFund;
	float phaseTol;
	float speedFund;
	float speedTol;
	float freqFund;
	float freqTol;

};

class baseSearch{

public:
	
	virtual vector<ofPtr<chime> >getChimes(searchData& sd, ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup) = 0;
	virtual void drawPreview(float dragDist, float dragAngle) = 0;
	
	virtual string setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub);
	void setName(string s);
	string getName();
	bool getIsSample();
	bool getIsMDrag();
	
	
protected:

	string name;
	string userDataString;
	vector <dataElement<float> > floatParameters;
	vector <dataElement<int> > intParameters;
	ofVec2f mDown, mDrag;
	bool isSample, isMDrag;
	
	enum e_fundType{
		FT_PHASE,
		FT_SPEED,
		FT_FREQ,
		FT_COUNT
	};
	
	
};