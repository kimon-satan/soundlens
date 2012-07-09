/*
 *  matchSearch.h
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "baseSearch.h"

class matchSearch : public baseSearch{
	
public:
	
	matchSearch();
	vector<ofPtr<chime> >getChimes(searchData& sd,ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup);
	virtual void drawPreview(float dragDist, float dragAngle);
	virtual string setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub);
	
protected:
	
	enum e_matchMode{
		
		MATCH_SIMPLE,
		MATCH_OR,
		MATCH_AND
	
	};
	
	int mTolIndex;
	int matchType;
	float mTol;
	
	
};