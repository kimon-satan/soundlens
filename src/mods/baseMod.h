/*
 *  baseMod.h
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "dataElement.h"
#include "chime.h"

class baseMod{

	public:
	
	virtual void makeMod(vector<ofPtr<chime> > chimes) = 0;
	virtual void drawControl(ofVec2f mouseDownPos, ofVec2f mouseDragPos, float dragDist, float dragAngle) = 0;
	
	void setName(string s);
	string setUserData(ofVec2f pos, float ua, float ub);
	
	protected:
	
	string name;
	string userDataString;
	vector <dataElement<float> > floatParameters;
	vector <dataElement<int> > intParameters;
	vector <dataElement<ofVec2f> > vecParameters;

};


