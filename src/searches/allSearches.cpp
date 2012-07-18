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
	
	ofPtr<matchSearch> mm = ofPtr<matchSearch>(new matchSearch());
	searches.push_back((ofPtr<baseSearch>)mm);

	for(int i = 0; i < 5; i++){
		ofPtr<predefMatchSearch> pm = ofPtr<predefMatchSearch>(new predefMatchSearch(i));
		searches.push_back((ofPtr<baseSearch>)pm);
	}
	
	for(int i = 0; i < 3; i++){
		ofPtr<fundSearch> bfs = ofPtr<fundSearch>(new fundSearch(i));
		searches.push_back((ofPtr<baseSearch>)bfs);
	}
	
	
	for(int i = 0; i < 3; i++){
		ofPtr<quantSearch> qs = ofPtr<quantSearch>(new quantSearch(i));
		searches.push_back((ofPtr<baseSearch>)qs);
	}
	
	for(int i = 0; i < 6; i++){
		ofPtr<filterSearch> qs = ofPtr<filterSearch>(new filterSearch(i));
		searches.push_back((ofPtr<baseSearch>)qs);
	}
	
	for(int i = 0; i < 2; i++){
		ofPtr<multiFilterSearch> mfs = ofPtr<multiFilterSearch>(new multiFilterSearch(i));
		searches.push_back((ofPtr<baseSearch>)mfs);
	}
	
	ofPtr<uniqueSearch> us = ofPtr<uniqueSearch>(new uniqueSearch());
	searches.push_back((ofPtr<baseSearch>)us);
	
	
	ofPtr<sieve> ss = ofPtr<sieve>(new sieve());
	searches.push_back((ofPtr<sieve>)ss);
	
	ofPtr<positionSearch> ps = ofPtr<positionSearch>(new positionSearch());
	searches.push_back((ofPtr<baseSearch>)ps);
	
	isSampleSelected = false;
	isSampleFound = false;
	
};


string allSearches::updateUserValues(int searchType, ofVec2f mD, ofVec2f mDr, float ua, float ub){
	
	string s = "";
	s = searches[searchType]->setUserData(mD, mDr, ua, ub);
	mDown.set(mD);
	mDrag.set(mDr);
	return s;
	
}

void allSearches::beginSearch(){
	
	if(isSampleFound)isSampleSelected = true;

}

vector<ofPtr<chime> >allSearches::search(int searchType, vector<ofPtr<chime> > searchGroup){
	
	if(searches[searchType]->getIsSample() && !isSampleSelected){
		
		pickSample(searchGroup, searches[searchType]->getIsMDrag());
		
		if(!isSampleFound)return searchGroup;
		
	}
	
	return searches[searchType]->getChimes(mSearchData, mSample, searchGroup);

}

void allSearches::drawSearch(int searchType, float dragDist, float dragAngle){
	
	searches[searchType]->drawPreview(dragDist, dragAngle);
	
}


void allSearches::pickSample(vector<ofPtr<chime> > searchGroup, bool isMDrag){
	
	float dist = 100.0f;
	
	isSampleFound = false;
	
	for(vector<ofPtr<chime> >::iterator it = searchGroup.begin(); it != searchGroup.end(); it++){
		
		float td = (isMDrag)? mDrag.distance((*it)->getStemDims().cPos) : mDown.distance((*it)->getStemDims().cPos);
		
		if(td < dist){
			dist = td;
			mSample = *it;
			isSampleFound = true;
		}
		
	}
	
	
}

void allSearches::reset(){
	
	isSampleSelected = false;
	isSampleFound = false;
	
}

//getters and setters

void allSearches::setSample(ofPtr<chime> s){mSample = s;}

ofPtr<chime> allSearches::getSample(){return mSample;}

string allSearches::getSearchName(int i){return searches[i]->getName();}

bool allSearches::getIsSampleSelected(){return isSampleSelected;}
bool allSearches::getIsSampleFound(){return isSampleFound;}
