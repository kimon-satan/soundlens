/*
 *  uniqueSearch.h
 *  testBed1
 *
 *  Created by Simon Katan on 16/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "baseSearch.h"

class uniqueSearch : public baseSearch{

	public:
	
	uniqueSearch();
	
	
	vector<ofPtr<chime> >getChimes(searchData& sd, ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup);
	void drawPreview(float dragDist, float dragAngle);
	string setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub);
	
	private:
	
	int paramType;
	

};