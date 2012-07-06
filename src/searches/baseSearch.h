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
	int phaseTol;

};

class baseSearch{

public:
	
	virtual vector<ofPtr<chime> >getChimes(searchData& sd, ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup) = 0;
	virtual void drawPreview(ofVec2f mouseDownPos, ofVec2f mouseDragPos, float dragDist, float dragAngle) = 0;
	
	string setUserData(float ua, float ub);
	void setName(string s);
	
protected:

	string name;
	string userDataString;
	vector <dataElement<float> > floatParameters;
	vector <dataElement<int> > intParameters;
	vector <dataElement<ofVec2f> > vecParameters;
	
};