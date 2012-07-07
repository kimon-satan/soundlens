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
	
	int phaseFund;
	float phaseTol;

};

class baseSearch{

public:
	
	virtual vector<ofPtr<chime> >getChimes(searchData& sd, ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup) = 0;
	virtual void drawPreview(float dragDist, float dragAngle) = 0;
	
	string setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub);
	void setName(string s);
	string getName();
	
protected:

	string name;
	string userDataString;
	vector <dataElement<float> > floatParameters;
	vector <dataElement<int> > intParameters;
	ofVec2f mDown, mDrag;
	
};