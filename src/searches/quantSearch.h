/*
 *  quantSearch.h
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "baseSearch.h"

class quantSearch : public baseSearch{
	
public:
	
	quantSearch(int fType);
	vector<ofPtr<chime> >getChimes(searchData& sd,ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup);
	void drawPreview(float dragDist, float dragAngle);
	
	
private:
	
	int fundType;
	
};