/*
 *  chimeManager.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 02/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "chimeManager.h"

vector<ofPtr<chime> > chimeManager::mChimes;
vector<ofPtr<chime> > chimeManager::mPreviewChimes;

vector<ofPtr<chime> > chimeManager::mSelected;
vector<ofPtr<chime> > chimeManager::mTmpSelected;
vector<vector<ofPtr<chime> > > chimeManager::mSelectionBank;
vector<vector<ofPtr<chime> > > chimeManager::renderList;

allSearches chimeManager::mSearchEngine;
allMods chimeManager::mModEngine;
ofxOscSender * chimeManager::iSender = NULL;

int chimeManager::sbIndex = 0;
float chimeManager::mMaxZ = 0.0f;
bool chimeManager::isNewSelection = false;
float chimeManager::flashAlpha = 0;
customListener chimeManager::mListener;

void chimeManager::setup(ofxOscSender & s, ofxOscSender & i_s){

	chimeUpdater::setOscSender(&s);
	chimeRenderer::loadSprites();
	
	iSender = &i_s;
	
	for(int i = 0; i < 100; i++){
		vector<ofPtr<chime> > tc;
		renderList.push_back(tc);
	}


}

string chimeManager::createChimes(groupPreset p, ofVec2f pos, float userA, float userB){
	
	mPreviewChimes.clear();
	
	p.aPos.initVal.abs_val.set(pos);
	
	string infoString = "";
	
	infoString = p.numChimes.setUserValues(userA, userB);
	infoString += p.aPos.setUserValues(userA, userB);
	
	for(int i = 0; i < p.fParams.size(); i++){
	
		infoString += p.fParams[i].setUserValues(userA, userB);
		
	}
	
	vector<int> nc;
	distributionEngine::makeValues(nc, p.numChimes);
	
	vector<vector<float> >modParams;
	
	//make the distributions
	
	for(int i = 0; i < CH_FLOAT_COUNT; i ++){
		vector<float> fVec;
		p.fParams[i].numVals = nc[0];
		distributionEngine::makeValues(fVec, p.fParams[i]);
		modParams.push_back(fVec);
	}
	
	vector<ofVec2f> aPositions;
	p.aPos.numVals = nc[0];
	distributionEngine::makeValues(aPositions, p.aPos);
	
	
	for(int i = 0; i < nc[0]; i ++){
		
		ofPtr<chime> c = ofPtr<chime>(new chime());
		
		for(int j = 0; j < CH_FLOAT_COUNT; j ++){
			
			//set the float count from the distributions just made
			c->setModParam(j, modParams[j][i]);
		}
		
		c->setAnchorPos(aPositions[i]);
		c->setSpIndex(100);
		c->setSensorColor(0, ofColor(255,0,0)); //needs to change
		c->setSensorColor(1, ofColor(255,0,0));
		
		c->setZpos(chimeUpdater::getFocalPoint() + 1.0); // needs changing
	
		
		mPreviewChimes.push_back(c);
		
	}
	
	//this may still move to mods ? 
	//nothing to handle position mapping here
	
	for(int j = 0; j < p.mapParams.size(); j++){

		vector<float> inVals;
		vector<float> outVals;
		vector<ofPtr<chime> >::iterator it;
		for(it = mPreviewChimes.begin(); it != mPreviewChimes.end(); it ++){
			
			inVals.push_back((*it)->getModParam(p.mapParams[j].inMap));
			
		}
		
		mappingEngine::makeMapping(inVals, outVals, p.mapParams[j]);
		
		int counter = 0;
		for(it = mPreviewChimes.begin(); it != mPreviewChimes.end(); it ++){
			
			(*it)->setModParam(p.mapParams[j].outMap, outVals[counter]);
			counter ++;
		}
		
		
	}
	
	//now update changes and init chimes
	
	for(vector<ofPtr<chime> >::iterator it = mPreviewChimes.begin(); it != mPreviewChimes.end(); it ++){
		chimeFactory::conformPhase(*it);
		chimeFactory::mapFreqToSensors(*it);
		
	}
	
	return infoString;
	
}

void chimeManager::endNewChimes(){

	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++)(*it)->setIsSelected(false);
	mSelected = mPreviewChimes;
	
	for(vector<ofPtr<chime> >::iterator it = mPreviewChimes.begin(); it != mPreviewChimes.end(); it++){
		(*it)->setIsSelected(true);
		chimeFactory::conformPhase(*it);
		chimeFactory::initBodies(*it);
		(*it)->setCollisionListener(mListener);
		mChimes.push_back(*it);
	}
	mPreviewChimes.clear();
	
	isNewSelection = true;
	
	if(mSelected.size() > 1){
		mSelectionBank.push_back(mSelected);
		isNewSelection = false;
	}
	
	rePopulateRenderList();

}

void chimeManager::rePopulateRenderList(){
	
	for(int i = 0; i < 100; i++)renderList[i].clear();
	
	
	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++){
		
		chimeUpdater::updateSpIndex(*it);
		int bin = (*it)->getSpIndex();
		if(bin < renderList.size()){
			renderList[bin].push_back(*it);
		}
		
		mMaxZ = max((*it)->getZpos(), mMaxZ);
		
	}
	
	
}


void chimeManager::shiftFocalPoint(float direction){
	
	float f = chimeUpdater::getFocalPoint();
	
	f =(direction > 0.1)? min(f + 0.005f, mMaxZ) : max(f - 0.005, 0.0);
	
	chimeUpdater::setFocalPoint(f);
	rePopulateRenderList();
	
	ofxOscMessage m;
	m.setAddress("/depthMeter");
	m.addFloatArg(f/mMaxZ);
	
	iSender->sendMessage(m);
	
	
}

void chimeManager::shiftZPos(float direction){
	
	float fp = chimeUpdater::getFocalPoint();
	
	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++){
		
		float d = fp - (*it)->getZpos();
		
		if(direction < 0.1){ //move twd focal point
			
			float a = (d != 0.0) ?((d > 0)? 0.005: -0.005) : 0.0;
			(*it)->setZpos((*it)->getZpos() + a);
			
		}else{
			
			//you can only move it just out of range
			//however could make this a delete trigger
			
			float a = (d > 0)? -0.005: 0.005;
			(*it)->setZpos(min(max((*it)->getZpos() + a, 0.0f), fp + 1.0f )); 
			
		}
		
	}
	
	rePopulateRenderList();
}


void chimeManager::switchSelBank(int i){
	
	if(mSelectionBank.size() > 0){
		sbIndex = min((int)mSelectionBank.size() - 1, max(sbIndex + i, 0));
		for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++)(*it)->setIsSelected(false);
		mSelected.clear();
		mSelected = mSelectionBank[sbIndex];
		for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++)(*it)->setIsSelected(true);
		flashAlpha = 255;
		isNewSelection = false;
	}
	
}


void chimeManager::saveSelBank(){

	if(isNewSelection){
		mSelectionBank.push_back(mSelected);
		flashAlpha = 255;
		isNewSelection = false;
	}
	
}

void chimeManager::clearSelBanks(){

	mSelectionBank.clear();
	sbIndex = 0;

}

void chimeManager::deleteSelBank(){
	
	if(!isNewSelection){
		mSelectionBank.erase(mSelectionBank.begin() + sbIndex);
		sbIndex = 0;
		isNewSelection = true;
	}
	
}


//selection methods

void chimeManager::newSearch(){

	clearTmps();
	mSearchEngine.reset();
	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++)(*it)->setIsSelected(false);
	mSelected = mChimes;
	
}


void chimeManager::beginSearch(){

	mSearchEngine.beginSearch();
	
}

string chimeManager::continueSearch(int searchType, ofVec2f mD, ofVec2f mDr, float userA, float userB){

	clearTmps();
	
	string s = mSearchEngine.updateUserValues(searchType, mD, mDr, userA, userB);
	
	if(mSelected.size() > 0){
		mTmpSelected =  mSearchEngine.search(searchType, mSelected);
	}
	
	return s;
	
}

void chimeManager::endSearch(){

	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++)(*it)->setIsSelected(false);
	mSelected.clear();
	mSelected = mTmpSelected;
	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++)(*it)->setIsSelected(true);
	clearTmps();
	
	if(mSelected.size() > 0)isNewSelection = true;
	
	
}


void chimeManager::clearTmps(){
		
	for(vector<ofPtr<chime> >::iterator it = mTmpSelected.begin(); it != mTmpSelected.end(); it++)(*it)->setIsTmpSelected(false);
	mTmpSelected.clear();
}




string chimeManager::continueMod(int modType, ofVec2f mD, ofVec2f mDr, float userA, float userB){

	string s = "";
	s = mModEngine.updateUserValues(modType, mD, mDr, userA, userB);
	return s;

}

void chimeManager::endMod(int modType){

	mModEngine.makeMod(modType, mSelected);
}

void chimeManager::incrementMod(int direction){

	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++)(*it)->stepIncrement(direction);
	
}

void chimeManager::update(){

	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++)chimeUpdater::update(*it);
	
	chimeUpdater::step();

}


void chimeManager::draw(){
	
	for(int i = renderList.size()-1; i > -1; i--){
		
		for(vector<ofPtr<chime> >::iterator it = renderList[i].begin(); it != renderList[i].end(); it++)chimeRenderer::draw(*it);
		
	}
	
	flashSelected();

}


void chimeManager::flashSelected(){
	
	if(flashAlpha > 0){
	
		for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++){
			chimeRenderer::drawOutline(*it, ofColor(205,50,120,flashAlpha));
		}
		
		flashAlpha -= 5;
		
	}

}

void chimeManager::drawSelected(){
	
	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++){
		if(!(*it)->getIsTmpSelected() && (*it)->getIsSelected())chimeRenderer::drawOutline(*it, ofColor(0,206,209,255));
	}


}

void chimeManager::drawTmpSelected(){
	
	for(vector<ofPtr<chime> >::iterator it = mTmpSelected.begin(); it != mTmpSelected.end(); it++){
		if((*it)->getIsTmpSelected())chimeRenderer::drawOutline(*it, ofColor(205,50,120,255));
	}
		
}

void chimeManager::drawSample(){
	
	if(mSearchEngine.getIsSampleSelected() || mSearchEngine.getIsSampleFound())
		chimeRenderer::drawHighlight(mSearchEngine.getSample(), ofColor(0,229,238,100));
	
}

void chimeManager::drawPreviewChimes(){

	for(vector<ofPtr<chime> >::iterator it = mPreviewChimes.begin(); it != mPreviewChimes.end(); it++){
		chimeRenderer::drawOutline(*it, ofColor(96,123,139));
	}
	

}

void chimeManager::drawSearchEngine(int searchType, float dragDist, float dragAngle){
	
	mSearchEngine.drawSearch(searchType, dragDist, dragAngle);

}

void chimeManager::drawModEngine(int searchType, float dragDist, float dragAngle){

	mModEngine.drawPreview(searchType, dragDist, dragAngle);
}


string chimeManager::getSearchName(int i){return mSearchEngine.getSearchName(i);}
string chimeManager::getModName(int i){return mModEngine.getModName(i);}
