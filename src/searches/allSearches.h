/*
 *  allSearches.h
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "matchSearch.h"
#include "baseFundSearch.h"
#include "quantSearch.h"
#include "positionSearch.h"
#include "predefMatchSearch.h"

enum e_SearchType {
	
	SEARCH_MATCH_MULTI,
	SEARCH_MATCH_PHASE,
	SEARCH_MATCH_SPEED,
	SEARCH_MATCH_LENGTH,
	
	SEARCH_MATCH_FREQ_OR,
	SEARCH_MATCH_FREQ_AND,
	SEARCH_MATCH_DECAY_OR,
	SEARCH_MATCH_DECAY_AND,
	
	SEARCH_SAMP_PHASE_FUND,
	SEARCH_QUANT_PHASE,
	SEARCH_POSITION,
	
	
	SEARCH_COUNT,
};


class allSearches{

	public:
	
	allSearches();
	
	void beginSearch();
	vector<ofPtr<chime> > search(int searchType, vector<ofPtr<chime> >  searchGroup);
	string updateUserValues(int searchType, ofVec2f mD, ofVec2f mDr, float ua, float ub);
	
	void drawSearch(int searchType,float dragDist, float dragAngle);
	
	
	//getters and setters
	
	void setSample(ofPtr<chime> s);
	ofPtr<chime> getSample();
	
	bool getIsSampleSelected();
	bool getIsSampleFound();
	
	void reset();
	
	string getSearchName(int i);
	
	private:
	
	void pickSample(vector<ofPtr<chime> > searchGroup, bool isMDrag);
	
	ofPtr<chime> mSample;
	searchData mSearchData;
	vector<ofPtr<baseSearch> > searches;
	bool isSampleSelected;
	bool isSampleFound;
	ofVec2f mDown, mDrag;


};