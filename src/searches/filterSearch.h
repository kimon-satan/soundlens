/*
 *  filterSearch.h
 *  testBed1
 *
 *  Created by Simon Katan on 10/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "baseSearch.h"


class filterSearch : public baseSearch{

	public:
	
	filterSearch(int pType);
	
	vector<ofPtr<chime> >getChimes(searchData& sd,ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup);
	void drawPreview(float dragDist, float dragAngle);
	
	
	private:
	
		
	
	int paramType;

};