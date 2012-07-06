/*
 *  speedSearch.h
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "baseSearch.h"

class speedSearch : public baseSearch{
	
public:
	
	speedSearch();
	vector<ofPtr<chime> >getChimes(searchData& sd,ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup);
	void drawPreview(ofVec2f mouseDownPos, ofVec2f mouseDragPos, float dragDist, float dragAngle);
	
	
private:
	
	
	
};