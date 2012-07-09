/*
 *  predefMatchSearch.h
 *  testBed1
 *
 *  Created by Simon Katan on 09/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "matchSearch.h"

class predefMatchSearch : public matchSearch{
	
	
	public:
	
	predefMatchSearch(int param);
	void drawPreview(float dragDist, float dragAngle);
	string setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub);



};