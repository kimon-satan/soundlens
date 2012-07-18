/*
 *  sieve.h
 *  testBed1
 *
 *  Created by Simon Katan on 18/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "baseSearch.h"
#include "tuningEngine.h"

class sieve : public baseSearch{
	
public:
	
	sieve();
	
	vector<ofPtr<chime> >getChimes(searchData& sd, ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup);
	void drawPreview(float dragDist, float dragAngle);
	
private:
	
	
	
};