/*
 *  allSearches.h
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "matchSearch.h"
#include "predefMatchSearch.h"
#include "fundSearch.h"
#include "quantSearch.h"
#include "filterSearch.h"
#include "multiFilterSearch.h"
#include "positionSearch.h"


enum e_SearchType {
	
	SEARCH_MATCH_MULTI,
	SEARCH_MATCH_PHASE,
	SEARCH_MATCH_SPEED,
	SEARCH_MATCH_LENGTH,
	
	SEARCH_MATCH_FREQ_OR,
	SEARCH_MATCH_FREQ_AND,
	SEARCH_MATCH_DECAY_OR,
	SEARCH_MATCH_DECAY_AND,
	
	SEARCH_FUND_PHASE,
	SEARCH_FUND_SPEED,
	SEARCH_FUND_FREQ,
	
	SEARCH_QUANT_PHASE,
	SEARCH_QUANT_SPEED,
	SEARCH_QUANT_FREQ,
	
	SEARCH_BPF_PHASE,
	SEARCH_BPF_SPEED,
	SEARCH_BPF_LENGTH,
	SEARCH_BPF_FDIST,
	SEARCH_BPF_FREQ,
	SEARCH_BPF_DECAY,
	
	SEARCH_MULTI_LPF,
	SEARCH_MULTI_HPF,

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