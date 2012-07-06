/*
 *  allSearches.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "allSearches.h"

allSearches::allSearches(){
	
	ofPtr<speedSearch> ss = ofPtr<speedSearch>(new speedSearch());
	searches.push_back((ofPtr<baseSearch>)ss);
	ofPtr<baseFundSearch> bfs = ofPtr<baseFundSearch>(new baseFundSearch());
	searches.push_back((ofPtr<baseSearch>)bfs);
	ofPtr<quantSearch> qs = ofPtr<quantSearch>(new quantSearch());
	searches.push_back((ofPtr<baseSearch>)qs);
	
};


string allSearches::updateUserValues(int searchType, float ua, float ub){
	
	string s = "";
	s = searches[searchType]->setUserData(ua, ub);
	return s;
	
}

vector<ofPtr<chime> >allSearches::search(int searchType, vector<ofPtr<chime> > searchGroup){
	

	return searches[searchType]->getChimes(mSearchData, mSample, searchGroup);

}

void allSearches::drawSearch(int searchType, ofVec2f mouseDownPos, ofVec2f mouseDragPos, float dragDist, float dragAngle){
	
	searches[searchType]->drawPreview(mouseDownPos, mouseDragPos, dragDist, dragAngle);
}


//getters and setters

void allSearches::setSample(ofPtr<chime> s){mSample = s;}

ofPtr<chime> allSearches::getSample(){return mSample;}


