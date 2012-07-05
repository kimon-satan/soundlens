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
vector<vector<ofPtr<chime> > > chimeManager::mPrevSelected;
vector<vector<ofPtr<chime> > > chimeManager::renderList;
ofxOscSender * chimeManager::iSender = NULL;

ofPtr<chime> chimeManager::mSampleChime;
float chimeManager::mPhaseTol = 0.0f;
int chimeManager::mPhaseFund = 64;

int chimeManager::prevSelIndex = 0;
float chimeManager::mMaxZ = 0.0f;
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
	
	p.pos.initVal =  pos;
	
	string infoString = "";
	
	infoString = p.numChimes.setUserValues(userA, userB);
	infoString += p.length.setUserValues(userA, userB);
	infoString += p.freq.setUserValues(userA, userB);
	infoString += p.speed.setUserValues(userA, userB);
	infoString += p.phase.setUserValues(userA, userB);
	
	int nc = p.numChimes.getValue();
	
	for(int i = 0; i < nc; i ++){
		
		chimeDef cd;
		cd.length = p.length.getValue(i,nc);
		cd.phase = p.phase.getValue(i,nc); 
		cd.anchorPos =  p.pos.getValue(i,nc);
		cd.offset = 0;	//ultimately remove this				
		cd.midi[0] = p.freq.getValue(i,nc);
		cd.midi[1] = p.freq.getValue(i,nc);
		cd.decay[0] = 1.8;
		cd.decay[1] = 1.8;
		cd.speed = p.speed.getValue(i,nc);
		cd.colors[0] = ofColor(255,0,0);
		cd.colors[1] = ofColor(255,0,0);
		cd.sensOn[0] = true;
		cd.sensOn[1] = true; 
		cd.zPos = chimeUpdater::getFocalPoint() + 1.0; //not for now
		
		
		ofPtr<chime> c = chimeFactory::createChime(cd);
		
		c->setCollisionListener(mListener);
		
		mPreviewChimes.push_back(c);

	}
	
	return infoString;
	

}

void chimeManager::endNewChimes(){

	mSelected = mPreviewChimes;
	for(vector<ofPtr<chime> >::iterator it = mPreviewChimes.begin(); it != mPreviewChimes.end(); it++)mChimes.push_back(*it);
	mPreviewChimes.clear();
	
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


void chimeManager::nextPrevSelected(){
	
	prevSelIndex = (prevSelIndex +1)%mPrevSelected.size();
	mSelected.clear();
	mSelected = mPrevSelected[prevSelIndex];
	
}

//selection methods

void chimeManager::newSearch(){

	clearTmps();
	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++)(*it)->setIsSelected(false);
	mSelected = mChimes;
	
}

void chimeManager::endSearch(){

	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++)(*it)->setIsSelected(false);
	mSelected.clear();
	mSelected = mTmpSelected;
	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++)(*it)->setIsSelected(true);
	clearTmps();
	
	
}


void chimeManager::clearTmps(){
	
	for(vector<ofPtr<chime> >::iterator it = mTmpSelected.begin(); it != mTmpSelected.end(); it++)(*it)->setIsTmpSelected(false);
	mTmpSelected.clear();
}


void chimeManager::selectSample(ofVec2f p){
	
	float dist = 100.0f;
	
	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++){
		
		float td = p.distance((*it)->getStemDims().cPos);
		if(td < dist){
			dist = td;
			mSampleChime = *it;
		}
		
	}	

}

void chimeManager::filterBySampleSpeed(){
	
	clearTmps();
	
	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++){
		
		if((*it)->getSpeed()  == mSampleChime->getSpeed()){
			mTmpSelected.push_back(*it);
			(*it)->setIsTmpSelected(true);
		}else{
			(*it)->setIsTmpSelected(false);
		}		
	}
	

}

void chimeManager::filterByPhaseFundamental(int pf, int tol){
	
	clearTmps();
	
	tol = max(tol, 1); //tol is in degrees
	float tol_r = tol * b2_pi/180;
	float angle = 2 * b2_pi/pf;
	
	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++){
		
		float rmdr = fmod((*it)->getPhase() - mSampleChime->getPhase(),angle);
		
		if(rmdr <= tol_r || angle - rmdr <= tol_r){
			mTmpSelected.push_back(*it);
			(*it)->setIsTmpSelected(true);
		}else{
			(*it)->setIsTmpSelected(false);
		}	
	}
	
	mPhaseFund = pf;

}

void chimeManager::filterByQInterval(int pMul, int pOff){
	
	vector<ofPtr<chime> > tmp;
	
	float tol = mPhaseTol;
	float angle = 2 * b2_pi/mPhaseFund;
	float offset = mSampleChime->getPhase() + (float)pOff * angle;
	angle *= pMul;
	
	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++){
		
		float rmdr = fmod((*it)->getPhase() - offset,angle);
		if(rmdr <= tol || angle - rmdr <= tol){
			mTmpSelected.push_back(*it);
			(*it)->setIsTmpSelected(true);
		}else{
			(*it)->setIsTmpSelected(false);
		}	
	}
	
	mTmpSelected = tmp;
	
}






void chimeManager::update(){

	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++)chimeUpdater::update(*it);
	
	chimeUpdater::step();

}


void chimeManager::draw(){
	
	for(int i = renderList.size()-1; i > -1; i--){
		
		for(vector<ofPtr<chime> >::iterator it = renderList[i].begin(); it != renderList[i].end(); it++)chimeRenderer::draw(*it);
		
	}
	

}


void chimeManager::drawSelected(){
	
	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++){
		if(!(*it)->getIsTmpSelected() && (*it)->getIsSelected())chimeRenderer::drawOutline(*it, ofColor(255,0,0,255));
	}


}

void chimeManager::drawTmpSelected(){
	
	for(vector<ofPtr<chime> >::iterator it = mTmpSelected.begin(); it != mTmpSelected.end(); it++){
		if((*it)->getIsTmpSelected())chimeRenderer::drawHighlight(*it, ofColor(255,0,0,50));
	}
		
}

void chimeManager::drawSample(){
	
	if(mSampleChime)chimeRenderer::drawHighlight(mSampleChime, ofColor(0,0,255,50));
	
}

void chimeManager::drawPreviewChimes(){

	for(vector<ofPtr<chime> >::iterator it = mPreviewChimes.begin(); it != mPreviewChimes.end(); it++){
		chimeRenderer::drawOutline(*it, ofColor(150,0,0,150));
	}
	

}

