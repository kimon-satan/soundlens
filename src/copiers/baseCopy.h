/*
 *  baseCopy.h
 *  testBed1
 *
 *  Created by Simon Katan on 18/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "baseMod.h"


struct copierSpec{
	
	int copierType;
	int chParam;
	dataElement<float> para1;
	dataElement<float> para2;
	
};


class baseCopy : public baseMod{

	public:
	
	virtual vector<ofPtr<chime> >getCopies(vector<ofPtr<chime> > chimes) = 0;
	vector<ofPtr<chime> >makeMod(vector<ofPtr<chime> > chimes, bool isAuto){};
	void drawControl(float dragDist, float dragAngle){};
	virtual string setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub);
	
	protected:
	
	int paramType;
	

};