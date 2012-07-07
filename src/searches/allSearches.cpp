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
	ofPtr<positionSearch> ps = ofPtr<positionSearch>(new positionSearch());
	searches.push_back((ofPtr<baseSearch>)ps);
	
};


string allSearches::updateUserValues(int searchType, ofVec2f mD, ofVec2f mDr, float ua, float ub){
	
	string s = "";
	s = searches[searchType]->setUserData(mD, mDr, ua, ub);
	return s;
	
}

vector<ofPtr<chime> >allSearches::search(int searchType, vector<ofPtr<chime> > searchGroup){
	
	return searches[searchType]->getChimes(mSearchData, mSample, searchGroup);

}

void allSearches::drawSearch(int searchType, float dragDist, float dragAngle){
	
	searches[searchType]->drawPreview(dragDist, dragAngle);
}


//getters and setters

void allSearches::setSample(ofPtr<chime> s){mSample = s;}

ofPtr<chime> allSearches::getSample(){return mSample;}


string allSearches::getSearchName(int i){return searches[i]->getName();}


