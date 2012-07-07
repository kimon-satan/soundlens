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
#include "positionSearch.h"

enum e_SearchType {
	SEARCH_SAMP_SPEED,
	SEARCH_SAMP_PHASE_FUND,
	SEARCH_QUANT_PHASE,
	SEARCH_POSITION_SEARCH,
	SEARCH_COUNT,
};


class allSearches{

	public:
	
	allSearches();
	
	vector<ofPtr<chime> > search(int searchType, vector<ofPtr<chime> >  searchGroup);
	string updateUserValues(int searchType, ofVec2f mD, ofVec2f mDr, float ua, float ub);
	
	void drawSearch(int searchType,float dragDist, float dragAngle);
	
	//getters and setters
	
	void setSample(ofPtr<chime> s);
	ofPtr<chime> getSample();
	string getSearchName(int i);
	
	private:
	
	ofPtr<chime> mSample;
	searchData mSearchData;
	vector<ofPtr<baseSearch> > searches;


};