/*
 *  allSearches.h
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "speedSearch.h"
#include "baseFundSearch.h"
#include "quantSearch.h"

enum e_SearchType {
	SEARCH_SAMP_SPEED,
	SEARCH_SAMP_PHASE_FUND,
	SEARCH_QUANT_PHASE,
	SEARCH_COUNT,
};


class allSearches{

	public:
	
	allSearches();
	
	vector<ofPtr<chime> > search(int searchType, vector<ofPtr<chime> >  searchGroup);
	string updateUserValues(int searchType, float ua, float ub);
	
	void drawSearch(int searchType, ofVec2f mouseDownPos, ofVec2f mouseDragPos, float dragDist, float dragAngle);
	
	//getters and setters
	
	void setSample(ofPtr<chime> s);
	ofPtr<chime> getSample();
	
	
	private:
	
	ofPtr<chime> mSample;
	searchData mSearchData;
	vector<ofPtr<baseSearch> > searches;


};