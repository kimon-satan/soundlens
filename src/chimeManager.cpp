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
vector<ofPtr<chime> > chimeManager::mCrossFaded;
vector<vector<ofPtr<chime> > > chimeManager::mHistory;
vector<vector<ofPtr<chime> > > chimeManager::renderList;
vector<vector<ofPtr<chime> > > chimeManager::mSaved;

allSearches chimeManager::mSearchEngine;
allMods chimeManager::mModEngine;
allCopiers chimeManager::mCopyEngine;

ofxOscSender * chimeManager::iSender = NULL;

int chimeManager::sbIndex = 0;
float chimeManager::mMaxZ = 0.0f;
bool chimeManager::isNewSelection = false;
float chimeManager::flashAlpha = 0;
customListener chimeManager::mListener;

bool isChimeHidden(ofPtr<chime> c){return (c->getBlur() > 0.99);}
bool isBankEmpty(vector<ofPtr<chime> > cVec){return (cVec.size() < 1);}

void chimeManager::setup(ofxOscSender & s, ofxOscSender & i_s){

	chimeUpdater::setOscSender(&s);
	chimeRenderer::loadSprites();
	
	iSender = &i_s;
	
	for(int i = 0; i < 100; i++){
		vector<ofPtr<chime> > tc;
		renderList.push_back(tc);
	}
	
	
	for(int i = 0; i < 10; i++){
		vector<ofPtr<chime> > t;
		mSaved.push_back(t);
	}

}


void chimeManager::createInitialChime(){

	chimeUpdater::setFocalPoint(1);
	
	ofPtr<chime> c = ofPtr<chime>(new chime());
	
	c->setFixedParam(CH_FREQ, 74);
	c->setFixedParam(CH_SPEED, 1.0);
	c->setFixedParam(CH_LENGTH, 2.0);
	c->setFixedParam(CH_PHASE, 1);
	c->setFixedParam(CH_DECAY, 1.8);
	c->setFixedParam(CH_COLOR, 255);
	
	c->setModParam(CH_PIV_NUM, 0);
	c->setModParam(CH_PIV_PH_MUL, 0);
	c->setModParam(CH_PIV_SPD_SKEW, 0);
	c->setModParam(CH_PIV_LGTH, 2);
	
	c->setAnchorPos(ofVec2f(0,0));
	c->setSpIndex(100);
	c->setZpos((chimeUpdater::getFocalPoint() > 1) ? 0 : 2);
	
	mPreviewChimes.push_back(c);
	endNewChimes();
	
	mSelected.clear();
	mSelected.push_back(c);

}


void chimeManager::beginCopy(copyPreset cp){
	
	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++)(*it)->endMods();
	mCopyEngine.beginCopy(cp);	

}

string chimeManager::continueCopy(ofVec2f mD, ofVec2f mDr, float userA, float userB){

	string s = "";
	s = mCopyEngine.updateUserValues(mD, mDr, userA, userB);
	mPreviewChimes = mCopyEngine.getCopies(mSelected);
	
	
	for(vector<ofPtr<chime> >::iterator it = mPreviewChimes.begin(); it != mPreviewChimes.end(); it ++){
		chimeUpdater::conformPhase(*it);
		chimeUpdater::updateDims(*it);
		chimeFactory::mapFreqToSensors(*it);
		
	}
	
	
	return s;
	

}

void chimeManager::endNewChimes(){
	
	
	if(isNewSelection && mSelected.size() > 0){
		mHistory.push_back(mSelected);
	}
	
	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++)(*it)->setIsSelected(false);
	mSelected = mPreviewChimes;
	
	for(vector<ofPtr<chime> >::iterator it = mPreviewChimes.begin(); it != mPreviewChimes.end(); it++){
		(*it)->setIsSelected(true);
		chimeFactory::mapFreqToSensors(*it);
		chimeUpdater::conformPhase(*it);
		chimeFactory::initBodies(*it);
		(*it)->setCollisionListener(mListener);
		mChimes.push_back(*it);
	}
	
	mPreviewChimes.clear();
	
	isNewSelection = true;
	
	if(mSelected.size() > 0){
		mHistory.push_back(mSelected);
		isNewSelection = false;
		sbIndex = mHistory.size() -1;
	}
	
	
	rePopulateRenderList();

}

void chimeManager::deleteHiddenChimes(){

	vector<ofPtr<chime> >::iterator it;
	
	
	for(int i =0; i < mSaved.size(); i++){
		it = remove_if(mSaved[i].begin(), mSaved[i].end(), isChimeHidden);
		mSaved[i].erase(it, mSaved[i].end());
	}
	
	
	
	for(int i =0; i < mHistory.size(); i++){
		it = remove_if(mHistory[i].begin(), mHistory[i].end(), isChimeHidden);
		mHistory[i].erase(it, mHistory[i].end());
	}
	
	//remove empty selection banks
	
	vector<vector<ofPtr<chime> > >::iterator it2;
	

	it2 = remove_if(mHistory.begin(), mHistory.end(), isBankEmpty);
	mHistory.erase(it2, mHistory.end());
	sbIndex = mHistory.size() -1;
	
	it = remove_if(mSelected.begin(), mSelected.end(), isChimeHidden);
	mSelected.erase(it, mSelected.end());
	
	it = remove_if(mTmpSelected.begin(), mTmpSelected.end(), isChimeHidden);
	mTmpSelected.erase(it, mTmpSelected.end());
	
	it = remove_if(mCrossFaded.begin(), mCrossFaded.end(), isChimeHidden);
	mCrossFaded.erase(it, mCrossFaded.end());
	
	it = remove_if(mChimes.begin(), mChimes.end(), isChimeHidden);
	mChimes.erase(it, mChimes.end());
	
	if(mChimes.size() == 0)createInitialChime();
	
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
	
	f = (direction > 0.1)? min(f + 0.01f, 2.0f) : max(f - 0.01f, 0.0f);
	
	chimeUpdater::setFocalPoint(f);
	rePopulateRenderList();
	
	/*ofxOscMessage m;
	m.setAddress("/depthMeter");
	m.addFloatArg(f/mMaxZ);
	
	iSender->sendMessage(m);*/
	
	
}


void chimeManager::shiftZPos(vector<ofPtr<chime> > & tChimes, float direction){

	float fp = chimeUpdater::getFocalPoint();
	
	
	for(vector<ofPtr<chime> >::iterator it = tChimes.begin(); it != tChimes.end(); it++){
		
		float d = fp - (*it)->getZpos();
		
		if(direction < 0.1){ //move twd focal point
			
			float a = (d != 0.0) ?((d > 0)? 0.005: -0.005) : 0.0;
			(*it)->setZpos((*it)->getZpos() + a);

		}else{
			
			float a = (d > 0)? -0.01: 0.01;
			
			//to allow always to move out of focus
			
			if(d >= 0 && fp < 1){
				(*it)->setZpos(fp + d);
				a = 0.01;
			}else if(d <= 0 && fp > 1){
				(*it)->setZpos(fp + d);
				a = -0.01;
			}
			
			(*it)->setZpos(min(max((*it)->getZpos() + a, 0.0f), 2.0f )); 
		}
		
	}
	
	rePopulateRenderList();
}

void chimeManager::shiftZPos(float direction){
	
	shiftZPos(mSelected, direction);
	if(isNewSelection)saveHistory();
	
}

void chimeManager::crossFade(float direction){
	
	if(mHistory.size() >= 2){
		shiftZPos(mHistory[mHistory.size() - 1], direction);
		shiftZPos(mHistory[mHistory.size() - 2], -direction);
	}
		
}


void chimeManager::equalizeZPos(){
	
	if(isNewSelection)saveHistory();
	
	vector<ofPtr<chime> >::iterator it; 
	
	float zTot = 0;

	for(it = mSelected.begin(); it != mSelected.end(); it++)zTot += (*it)->getZpos();
	
	zTot /= (float)mSelected.size();
	
	for(it = mSelected.begin(); it != mSelected.end(); it++){
		
		float d = ((*it)->getZpos() < zTot)? 0.01 : - 0.01;
		(*it)->setZpos((*it)->getZpos() + d);
	
	}
		
	rePopulateRenderList();
}




void chimeManager::incrHistory(int i){
	
	if(mHistory.size() > 0){
		sbIndex = min((int)mHistory.size() - 1, max(sbIndex + i, 0));
		for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++)(*it)->setIsSelected(false);
		mSelected.clear();
		mSelected = mHistory[sbIndex];
		for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++)(*it)->setIsSelected(true);
		flashAlpha = 255;
		isNewSelection = false;
	}
	
}


void chimeManager::saveHistory(){

	if(isNewSelection){
		mHistory.push_back(mSelected);
		flashAlpha = 255;
		isNewSelection = false;
		sbIndex = mHistory.size() -1;
	}
	
}

void chimeManager::saveToBank(int i){

	mSaved[i] = mSelected;
	flashAlpha = 255;
	isNewSelection = true;
	saveHistory();
	
}

void chimeManager::switchToBank(int i, bool merge){
	
	vector<ofPtr<chime> >::iterator it;
	
	if(merge){
		
		for(it = mSaved[i].begin(); it != mSaved[i].end(); it++){
			(*it)->setIsSelected(true);
			mSelected.push_back((*it));
		}
		
		sort(mSelected.begin(), mSelected.end());
		it = unique(mSelected.begin(), mSelected.end());
		mSelected.resize(it - mSelected.begin());
	
	}else{
	
		for(it = mSelected.begin(); it != mSelected.end(); it++)(*it)->setIsSelected(false);
		mSelected = mSaved[i];
	
	}
	
	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++)(*it)->setIsSelected(true);
	flashAlpha = 255;

}


//selection methods

void chimeManager::newSearch(bool useResults){

	clearTmps();
	mSearchEngine.reset();
	
	if(!useResults){
		for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++)(*it)->setIsSelected(false);
		mSelected = mChimes;
	}
	
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


void chimeManager::invertSelection(){
	
	clearTmps();
	
	vector<ofPtr<chime> >tmp;
	
	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++){
		
		if(!(*it)->getIsSelected()){
			(*it)->setIsSelected(true);
			tmp.push_back(*it);
		}else{
			(*it)->setIsSelected(false);
		}
		
	}
	
	flashAlpha = 255;
	mSelected.clear();
	mSelected = tmp;
	
	isNewSelection = true;

}

void chimeManager::clearTmps(){
		
	for(vector<ofPtr<chime> >::iterator it = mTmpSelected.begin(); it != mTmpSelected.end(); it++)(*it)->setIsTmpSelected(false);
	mTmpSelected.clear();
}


void chimeManager::clearAllMods(){

	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++){
	
		(*it)->endMods();
	
	}
}

void chimeManager::beginMod(bool isAuto){

	mModEngine.setIsAuto(isAuto);

}

string chimeManager::continueMod(int modType, ofVec2f mD, ofVec2f mDr, float userA, float userB){

	string s = "";
	s = mModEngine.updateUserValues(modType, mD, mDr, userA, userB);
	return s;

}

void chimeManager::endMod(int modType){
	
	mModEngine.makeMod(modType, mSelected);
	
	if(isNewSelection)saveHistory();
	
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

void chimeManager::drawCopyEngine(float dragDist, float dragAngle){
	
	mCopyEngine.drawPreview(dragDist, dragAngle);
}

string chimeManager::getSearchName(int i){return mSearchEngine.getSearchName(i);}
string chimeManager::getModName(int i){return mModEngine.getModName(i);}
