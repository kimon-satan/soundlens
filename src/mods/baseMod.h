/*
 *  baseMod.h
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


#include "distributionEngine.h"
#include "chime.h"

class baseMod{

	public:
	
	virtual vector<ofPtr<chime> >makeMod(vector<ofPtr<chime> > chimes) = 0;
	virtual vector<ofPtr<chime> >makeMod(vector<ofPtr<chime> > chimes, bool isAuto) = 0;
	virtual void drawControl( float dragDist, float dragAngle) = 0;
	
	void setName(string s);
	string getName();
	virtual string setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub);
	
	
	
	protected:
	
	string name;
	string userDataString;
	vector <dataElement<float> > floatParameters;
	vector <dataElement<int> > intParameters;

	ofVec2f mDown;
	ofVec2f mDrag;
	
	

};


